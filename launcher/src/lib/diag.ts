// "Collect logs" and "Report a problem": the report zip is written by the
// Rust side (diag.rs), which also takes the user's home folder and name out;
// this side adds the output of recent tasks and asks where to save it.
import { api, pickZip } from "./api";
import { guard, jobs, toast, type Job } from "./app.svelte";
import { elapsed } from "./format";

/** The issue form the maintainers keep in .github/ISSUE_TEMPLATE. */
export const REPORT_URL = "https://github.com/Veradictus/Thief3-Decomp/issues/new?template=bug_report.yml";

/** The output of the most recent tasks, oldest first, each cut to its last lines. */
export function taskLogText(list: Job[], maxJobs = 10, maxLines = 400): string {
  return list
    .filter((j) => j.state !== "queued")
    .slice(-maxJobs)
    .map((j) => {
      const exit = j.code === null ? "" : `, exit code ${j.code.toString()}`;
      const time = j.started ? `, ${elapsed(j.started, j.ended)}` : "";
      const lines = j.lines.slice(-maxLines).map((l) => (l.stream === "stderr" ? `! ${l.line}` : l.line));
      const cut =
        j.lines.length > maxLines ? [`[${(j.lines.length - maxLines).toString()} earlier lines left out]`] : [];
      return [
        `== ${j.title} (${j.state}${exit}${time})`,
        ...(j.command ? [`$ ${j.command}`] : []),
        ...cut,
        ...lines,
      ].join("\n");
    })
    .join("\n\n");
}

/** "T3SDK-report-2026-09-28.zip", in local time. */
export function reportName(date: Date): string {
  const pad = (n: number) => n.toString().padStart(2, "0");
  return `T3SDK-report-${date.getFullYear().toString()}-${pad(date.getMonth() + 1)}-${pad(date.getDate())}.zip`;
}

export async function collectLogs() {
  const path = await guard(pickZip("Save the report", reportName(new Date())));
  if (!path) return;
  const report = await guard(api.collectLogs(path, taskLogText(jobs.list) || null));
  if (report) {
    const name = report.path.split(/[\\/]/).pop() ?? report.path;
    toast(`Saved ${name} (${report.files.toString()} files). Attach it to your report.`);
  }
}

export function reportProblem() {
  void guard(api.openLink(REPORT_URL));
}
