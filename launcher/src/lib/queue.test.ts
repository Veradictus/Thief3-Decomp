// The job queue runs against the browser mock (no Tauri here), with fake
// timers standing in for the tools' running time.
import { afterEach, beforeEach, describe, expect, it, vi } from "vitest";
import { api } from "./api";
import { cancel, clearFinished, enqueue, jobs, pending, running } from "./app.svelte";

// Long enough for one mock job: its command delay plus its scripted output and
// exit (about 1.8 s), and short of a second one.
const RUN_MS = 2000;

describe("job queue", () => {
  beforeEach(() => {
    vi.useFakeTimers();
  });
  afterEach(async () => {
    await vi.runAllTimersAsync();
    clearFinished();
    vi.useRealTimers();
    vi.restoreAllMocks();
  });

  it("runs jobs one at a time, in order", async () => {
    const first = enqueue({ kind: "export", level: "Inn" }, "Export Inn");
    const second = enqueue({ kind: "import" }, "Import into Godot");
    await vi.advanceTimersByTimeAsync(100);
    expect(running()?.key).toBe(first.key);
    expect(second.state).toBe("queued");
    expect(pending()).toBe(2);

    await vi.advanceTimersByTimeAsync(RUN_MS);
    expect(first.state).toBe("done");
    expect(first.lines.length).toBeGreaterThan(0);
    expect(running()?.key).toBe(second.key);

    await vi.advanceTimersByTimeAsync(RUN_MS);
    expect(second.state).toBe("done");
    expect(pending()).toBe(0);
  });

  it("skips a job whose prerequisite failed", async () => {
    vi.spyOn(api, "startTask").mockRejectedValueOnce("python not found");
    const exportJob = enqueue({ kind: "export", level: "Inn" }, "Export Inn");
    const importJob = enqueue({ kind: "import" }, "Import into Godot", exportJob);
    await vi.advanceTimersByTimeAsync(RUN_MS);
    expect(exportJob.state).toBe("failed");
    expect(exportJob.lines.at(-1)?.line).toBe("python not found");
    expect(importJob.state).toBe("cancelled");
    expect(importJob.lines.at(-1)?.line).toContain("did not succeed");
  });

  it("runs a job's follow-up only when it succeeds", async () => {
    const opened: string[] = [];
    const ok = enqueue({ kind: "export", level: "Inn" }, "Update Inn", null, () => opened.push("Inn"));
    await vi.advanceTimersByTimeAsync(RUN_MS);
    expect(ok.state).toBe("done");
    expect(opened).toEqual(["Inn"]);

    vi.spyOn(api, "startTask").mockRejectedValueOnce("python not found");
    enqueue({ kind: "export", level: "Docks" }, "Update Docks", null, () => opened.push("Docks"));
    await vi.advanceTimersByTimeAsync(RUN_MS);
    expect(opened).toEqual(["Inn"]);
  });

  it("drops a queued job that is cancelled before it starts", async () => {
    const first = enqueue({ kind: "sdkDeploy" }, "Install T3SDK");
    const second = enqueue({ kind: "restore", level: null }, "Restore all maps");
    cancel(second);
    await vi.advanceTimersByTimeAsync(2 * RUN_MS);
    expect(first.state).toBe("done");
    expect(second.state).toBe("cancelled");
    expect(second.started).toBeNull();
  });

  it("keeps only unfinished jobs when clearing", async () => {
    enqueue({ kind: "godotCheck" }, "Check the Godot project");
    await vi.advanceTimersByTimeAsync(RUN_MS);
    enqueue({ kind: "sdkBuild" }, "Build T3SDK");
    clearFinished();
    expect(jobs.list.map((j) => j.title)).toEqual(["Build T3SDK"]);
  });
});
