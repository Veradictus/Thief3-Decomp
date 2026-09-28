import { describe, expect, it } from "vitest";
import type { Job } from "./app.svelte";
import { reportName, taskLogText } from "./diag";

function job(key: number, state: Job["state"], lines: string[], extra: Partial<Job> = {}): Job {
  return {
    key,
    spec: { kind: "sdkDeploy" },
    title: `Job ${key.toString()}`,
    state,
    id: key,
    command: `python tools/sdk.py deploy`,
    lines: lines.map((line) => ({ stream: line.startsWith("error") ? "stderr" : "stdout", line })),
    code: state === "done" ? 0 : state === "failed" ? 1 : null,
    started: 1000,
    ended: state === "running" ? null : 5200,
    requires: null,
    onDone: null,
    ...extra,
  };
}

describe("task logs for a report", () => {
  it("lists finished and running jobs with their output", () => {
    const text = taskLogText([
      job(1, "done", ["installed dinput8.dll"]),
      job(2, "failed", ["copying", "error: access denied"]),
      job(3, "queued", []),
    ]);
    expect(text).toBe(
      [
        "== Job 1 (done, exit code 0, 4.2 s)",
        "$ python tools/sdk.py deploy",
        "installed dinput8.dll",
        "",
        "== Job 2 (failed, exit code 1, 4.2 s)",
        "$ python tools/sdk.py deploy",
        "copying",
        "! error: access denied",
      ].join("\n"),
    );
  });

  it("keeps only the newest jobs and the end of long output", () => {
    const many = Array.from({ length: 12 }, (_, i) => job(i + 1, "done", ["a", "b", "c"], { command: "" }));
    const text = taskLogText(many, 2, 2);
    expect(text.match(/^== /gm)).toHaveLength(2);
    expect(text).toContain("== Job 11");
    expect(text).toContain("[1 earlier lines left out]\nb\nc");
    expect(text).not.toContain("$ ");
  });

  it("is empty with nothing run", () => {
    expect(taskLogText([])).toBe("");
  });
});

describe("report name", () => {
  it("carries the local date", () => {
    expect(reportName(new Date(2026, 8, 28, 23, 59))).toBe("T3SDK-report-2026-09-28.zip");
    expect(reportName(new Date(2027, 0, 5))).toBe("T3SDK-report-2027-01-05.zip");
  });
});
