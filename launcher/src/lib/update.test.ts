// The update flow against the browser mock (no Tauri here), with fake timers
// standing in for the download.
import { afterEach, beforeEach, describe, expect, it, vi } from "vitest";
import { api, onEvent, type UpdateProgress } from "./api";
import { app } from "./app.svelte";
import { percent } from "./format";
import { checkForUpdate, installUpdate, startupUpdateCheck, updater } from "./update.svelte";

const found = {
  version: "0.2.0",
  currentVersion: "0.1.0",
  notes: "See https://example.org/v0.2.0",
  date: 1_790_000_000,
};

describe("updates", () => {
  beforeEach(() => {
    vi.useFakeTimers();
    Object.assign(updater, { update: null, checked: false, error: "", dismissed: false, installing: false });
  });
  afterEach(async () => {
    await vi.runAllTimersAsync();
    vi.useRealTimers();
    vi.restoreAllMocks();
  });

  it("checks at start-up and remembers what it found", async () => {
    const check = vi.spyOn(api, "checkUpdate").mockResolvedValue({ checked: true, update: found });
    const done = startupUpdateCheck();
    await vi.runAllTimersAsync();
    await done;
    expect(check).toHaveBeenCalledWith(true);
    expect(updater.status?.enabled).toBe(true);
    expect(updater.update?.version).toBe("0.2.0");
    expect(updater.checked).toBe(true);
  });

  it("leaves the state alone when the start-up check is skipped", async () => {
    updater.update = found;
    vi.spyOn(api, "checkUpdate").mockResolvedValue({ checked: false, update: null });
    const done = checkForUpdate(true);
    await vi.runAllTimersAsync();
    await done;
    expect(updater.update).toEqual(found);
    expect(updater.checked).toBe(false);
  });

  it("keeps a failed start-up check quiet but reports a manual one", async () => {
    vi.spyOn(api, "checkUpdate").mockRejectedValue("offline");
    const toasts = app.toasts.length;
    const auto = checkForUpdate(true);
    await vi.advanceTimersByTimeAsync(0);
    await auto;
    expect(updater.error).toBe("offline");
    expect(updater.checking).toBe(false);
    expect(app.toasts).toHaveLength(toasts);

    const manual = checkForUpdate(false);
    await vi.advanceTimersByTimeAsync(0);
    await manual;
    expect(app.toasts.at(-1)).toMatchObject({ text: "offline", kind: "error" });
  });

  it("follows the download and clears the update once installed", async () => {
    updater.update = found;
    const events: UpdateProgress[] = [];
    const shown: (UpdateProgress | null)[] = [];
    const stop = await onEvent<UpdateProgress>("update-progress", (p) => events.push(p));
    const install = installUpdate();
    expect(updater.installing).toBe(true);
    for (let i = 0; i < 20; i++) {
      await vi.advanceTimersByTimeAsync(100);
      shown.push(updater.progress && { ...updater.progress });
    }
    await install;
    stop();
    expect(events.at(-1)?.finished).toBe(true);
    const halfway = shown.find((p) => p?.total && p.downloaded > 0);
    expect(halfway && percent(halfway.downloaded, halfway.total)).toBeGreaterThan(0);
    expect(updater.installing).toBe(false);
    expect(updater.progress).toBeNull();
    expect(updater.update).toBeNull();
  });
});
