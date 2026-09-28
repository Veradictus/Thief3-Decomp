import { describe, expect, it } from "vitest";
import type { IndexMod, IndexVersion, ModList, ModPackage, SyncReport } from "./api";
import {
  badges,
  compareVersions,
  dropIndex,
  indexTags,
  installButton,
  issuesFor,
  listText,
  matches,
  meta,
  moveBefore,
  moveBy,
  moveTo,
  reportText,
  textureJobTitle,
  textureSteps,
  worst,
} from "./modlist";

const order = ["a", "b", "c", "d"];

describe("load order moves", () => {
  it("moves to an index of the result", () => {
    expect(moveTo(order, "a", 2)).toEqual(["b", "c", "a", "d"]);
    expect(moveTo(order, "d", 0)).toEqual(["d", "a", "b", "c"]);
    expect(moveTo(order, "b", 99)).toEqual(["a", "c", "d", "b"]);
    expect(moveTo(order, "x", 0)).toBe(order);
  });
  it("moves up and down by one, staying in the list", () => {
    expect(moveBy(order, "c", -1)).toEqual(["a", "c", "b", "d"]);
    expect(moveBy(order, "c", 1)).toEqual(["a", "b", "d", "c"]);
    expect(moveBy(order, "a", -1)).toEqual(order);
  });
  it("moves a requirement before the mod that needs it", () => {
    expect(moveBefore(order, "d", "b")).toEqual(["a", "d", "b", "c"]);
    expect(moveBefore(order, "a", "c")).toEqual(["b", "a", "c", "d"]);
    expect(moveBefore(order, "a", "x")).toBe(order);
  });
  it("finds where a dragged row lands", () => {
    const middles = [10, 30, 50, 70];
    expect(dropIndex(middles, 5, 2)).toBe(0);
    expect(dropIndex(middles, 45, 0)).toBe(1);
    expect(dropIndex(middles, 65, 0)).toBe(2);
    expect(dropIndex(middles, 100, 1)).toBe(3);
    expect(dropIndex(middles, 49, 2)).toBe(2);
  });
});

const pkg = (p: Partial<ModPackage>): ModPackage => ({
  id: "m",
  name: "M",
  version: "1.0.0",
  authors: [],
  description: null,
  homepage: null,
  license: null,
  tags: [],
  entry: null,
  api: null,
  requires: {},
  conflicts: [],
  enabled: true,
  active: true,
  position: 0,
  size: 0,
  code: false,
  files: 0,
  textures: 0,
  error: null,
  ...p,
});

describe("packages and issues", () => {
  it("shows what a package holds", () => {
    expect(badges(pkg({ code: true, entry: "m.dll", files: 1, textures: 12 })).map((b) => b.key)).toEqual([
      "code",
      "content",
      "textures",
    ]);
    expect(badges(pkg({ files: 1 }))[0]?.title).toBe("1 file placed in the game folder");
    expect(badges(pkg({}))).toEqual([]);
  });
  it("sorts a package's issues worst first", () => {
    const list = {
      issues: [
        { severity: "info", mod: "a", message: "i", fix: null },
        { severity: "error", mod: "a", message: "e", fix: null },
        { severity: "warning", mod: null, message: "w", fix: null },
      ],
    } as unknown as ModList;
    expect(issuesFor(list, "a").map((i) => i.message)).toEqual(["e", "i"]);
    expect(issuesFor(list, null).map((i) => i.message)).toEqual(["w"]);
    expect(issuesFor(null, "a")).toEqual([]);
    expect(worst(list.issues)).toBe("error");
    expect(worst([])).toBeNull();
  });
  it("joins the parts of a line that are set", () => {
    expect(meta("by A", null, "m", false, undefined, "", 12)).toBe("by A · m · 12");
    expect(meta()).toBe("");
  });
  it("joins names", () => {
    expect(listText([])).toBe("");
    expect(listText(["A"])).toBe("A");
    expect(listText(["A", "B", "C"])).toBe("A, B and C");
  });
  it("says what a change did", () => {
    const report: SyncReport = {
      placed: 0,
      restored: 0,
      changed: [],
      errors: [],
      skipped: [],
      installed: null,
      removed: null,
    };
    expect(reportText(null)).toBeNull();
    expect(reportText(report)).toBeNull();
    const installed = { id: "m", name: "M", version: "1.2.0", previous: null };
    expect(reportText({ ...report, installed })).toBe("Installed M 1.2.0.");
    expect(reportText({ ...report, installed: { ...installed, previous: "1.0.0" } })).toBe("M: 1.0.0 → 1.2.0.");
    expect(reportText({ ...report, removed: "m", skipped: ["x"] })).toBe("Removed m. Not installed, skipped: x.");
  });
});

describe("texture packs", () => {
  const t = (needed: boolean, mods: string[], bundles: string[] = []) => ({ needed, mods, bundles });
  it("applies when the packs changed, restoring when none is left", () => {
    expect(textureSteps(t(false, ["hd"]), [])).toBeNull();
    expect(textureSteps(t(true, ["hd"]), [])).toEqual({ restore: false, apply: ["hd"] });
    expect(textureSteps(t(true, []), [])).toEqual({ restore: false, apply: [] });
    expect(textureJobTitle([])).toBe("Restore the original textures");
  });
  it("does not queue the same apply twice, unless asked again", () => {
    expect(textureSteps(t(true, ["hd"]), [["hd"]])).toBeNull();
    expect(textureSteps(t(true, ["hd", "x"]), [["hd"]])).toEqual({ restore: false, apply: ["hd", "x"] });
    expect(textureSteps(t(false, ["hd"]), [["hd"]], true)).toEqual({ restore: false, apply: ["hd"] });
  });
  it("restores first when bundles wait, then applies the packs again", () => {
    const bundles = ["Content/T3/Maps/Inn.ibt"];
    expect(textureSteps(t(false, ["hd"], bundles), [["hd"]])).toEqual({ restore: true, apply: ["hd"] });
    expect(textureSteps(t(true, [], bundles), [])).toEqual({ restore: true, apply: null });
  });
});

const version = (v: string, compatible = true): IndexVersion => ({
  version: v,
  url: `https://example.org/${v}.t3mod`,
  size: 1,
  released: null,
  api: null,
  requires: {},
  conflicts: [],
  compatible,
  notes: [],
});

const entry = (m: Partial<IndexMod>): IndexMod => ({
  id: "lockpicks",
  name: "Better Lockpicks",
  description: "Lockpicking without the fuss.",
  authors: ["Someone"],
  homepage: null,
  license: null,
  tags: ["gameplay"],
  installed: null,
  enabled: false,
  versions: [version("1.2.0")],
  recommended: "1.2.0",
  ...m,
});

describe("the index browser", () => {
  it("searches every word in names, authors, descriptions and tags", () => {
    expect(matches(entry({}), "", null)).toBe(true);
    expect(matches(entry({}), "lock FUSS", null)).toBe(true);
    expect(matches(entry({}), "someone gameplay", "gameplay")).toBe(true);
    expect(matches(entry({}), "lock", "ui")).toBe(false);
    expect(matches(entry({}), "lock textures", null)).toBe(false);
  });
  it("lists tags by use", () => {
    const mods = [entry({ tags: ["ui", "graphics"] }), entry({ tags: ["ui"] }), entry({ tags: ["audio"] })];
    expect(indexTags(mods)).toEqual(["ui", "audio", "graphics"]);
  });
  it("orders semantic versions", () => {
    expect(compareVersions("1.10.0", "1.9.0")).toBe(1);
    expect(compareVersions("1.0.0", "1.0.0+build")).toBe(0);
    expect(compareVersions("1.0.0-beta", "1.0.0")).toBe(-1);
    expect(compareVersions("1.0.0-beta.2", "1.0.0-beta.10")).toBe(-1);
    expect(compareVersions("1.0.0-alpha.1", "1.0.0-alpha")).toBe(1);
    expect(compareVersions("1.0.0-1", "1.0.0-alpha")).toBe(-1);
  });
  it("offers install, update, or nothing", () => {
    expect(installButton(entry({}), version("1.2.0"))).toEqual({
      label: "Install 1.2.0",
      version: "1.2.0",
      primary: true,
    });
    expect(installButton(entry({}), version("1.2.0", false)).primary).toBe(false);
    expect(installButton(entry({ installed: "1.2.0" }), version("1.2.0")).version).toBeNull();
    expect(installButton(entry({ installed: "1.0.0" }), version("1.2.0")).label).toBe("Update to 1.2.0");
    expect(installButton(entry({ installed: "2.0.0" }), version("1.2.0")).label).toBe("Install 1.2.0 (older)");
    expect(installButton(entry({}), undefined).version).toBeNull();
  });
});
