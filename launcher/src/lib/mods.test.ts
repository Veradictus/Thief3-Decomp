// The Mods page's store against the browser mock (no Tauri here), with fake
// timers standing in for the mock's delays and download.
import { afterEach, beforeEach, describe, expect, it, vi } from "vitest";
import { clearFinished, jobs } from "./app.svelte";
import {
  fix,
  installFiles,
  installFromIndex,
  loadIndex,
  loadMods,
  mods,
  profile,
  setPackageEnabled,
} from "./mods.svelte";

describe("mods store", () => {
  beforeEach(() => {
    vi.useFakeTimers();
  });
  afterEach(async () => {
    await vi.runAllTimersAsync();
    clearFinished();
    vi.useRealTimers();
  });

  const run = async <T>(work: Promise<T>): Promise<T> => {
    const done = work;
    await vi.runAllTimersAsync();
    return done;
  };

  it("lists packages in load order, with issues", async () => {
    await run(loadMods());
    const ids = mods.list?.packages.map((p) => p.id) ?? [];
    expect(ids[0]).toBe("sdk-ui-helpers");
    expect(mods.list?.loose.length).toBeGreaterThan(0);
  });

  it("queues the texture packs when they change", async () => {
    await run(setPackageEnabled("hd-textures", true));
    expect(mods.list?.textures.mods).toEqual(["hd-textures"]);
    const job = jobs.list.find((j) => j.spec.kind === "texturePacks");
    expect(job?.spec).toEqual({ kind: "texturePacks", mods: ["hd-textures"] });
    await run(Promise.resolve());
    await run(setPackageEnabled("hd-textures", false));
    const last = jobs.list.filter((j) => j.spec.kind === "texturePacks").at(-1);
    expect(last?.spec).toEqual({ kind: "texturePacks", mods: [] });
  });

  it("applies a fix and reports a missing requirement", async () => {
    await run(setPackageEnabled("sdk-ui-helpers", false));
    const issue = mods.list?.issues.find((i) => i.mod === "better-lockpicks" && i.fix);
    expect(issue?.fix?.action).toEqual({ kind: "enable", id: "sdk-ui-helpers" });
    if (issue?.fix) await run(fix(issue.fix.action));
    expect(mods.list?.packages.find((p) => p.id === "sdk-ui-helpers")?.enabled).toBe(true);
    await run(setPackageEnabled("coop-prototype", true));
    const coop = mods.list?.packages.find((p) => p.id === "coop-prototype");
    expect(coop?.enabled && !coop.active).toBe(true);
  });

  it("installs dropped packages and ignores other files", async () => {
    await run(installFiles(["C:\\Downloads\\readme.txt"]));
    await run(installFiles(["C:\\Downloads\\night-vision-1.0.0.t3mod"]));
    expect(mods.list?.packages.at(-1)?.id).toBe("night-vision");
    expect(mods.list?.report?.installed?.version).toBe("1.0.0");
  });

  it("switches profiles", async () => {
    await run(profile({ kind: "saveAs", name: "Coop" }));
    expect(mods.list?.profile).toBe("Coop");
    await run(profile({ kind: "switch", name: "Vanilla" }));
    expect(mods.list?.packages.every((p) => !p.enabled)).toBe(true);
    await run(profile({ kind: "switch", name: "Coop" }));
    expect(mods.list?.packages.some((p) => p.enabled)).toBe(true);
  });

  it("finds updates in the index and installs one", async () => {
    await run(loadIndex(true));
    const update = mods.index?.updates.find((u) => u.id === "better-lockpicks");
    expect(update?.latest).toBe("1.3.0");
    const coop = mods.index?.mods.find((m) => m.id === "coop-prototype");
    expect(coop?.versions[0]?.compatible).toBe(false);
    await run(installFromIndex("better-lockpicks", "1.3.0"));
    expect(mods.list?.packages.find((p) => p.id === "better-lockpicks")?.version).toBe("1.3.0");
    expect(mods.download).toBeNull();
    await run(loadIndex(false));
    expect(mods.index?.updates.some((u) => u.id === "better-lockpicks")).toBe(false);
  });
});
