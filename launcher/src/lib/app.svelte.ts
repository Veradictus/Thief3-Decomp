// Shared UI state: the config, the status overview, navigation, toasts, and the
// job queue. Jobs run one at a time, in order, so two tools never write the
// same Godot project or game folder at once.
import { api, errorText, onEvent, type Config, type Overview, type TaskExit, type TaskOutput, type TaskSpec } from "./api";

export type Page = "play" | "maps" | "mods" | "sdk" | "tasks" | "settings";

export const app = $state({
  config: null as Config | null,
  overview: null as Overview | null,
  page: "play" as Page,
  toasts: [] as { id: number; text: string; kind: "info" | "error" }[],
  /** Bumped when files may have changed, so pages reload their lists. */
  revision: 0,
});

let toastId = 0;
export function toast(text: string, kind: "info" | "error" = "info") {
  const id = ++toastId;
  app.toasts.push({ id, text, kind });
  setTimeout(() => (app.toasts = app.toasts.filter((t) => t.id !== id)), kind === "error" ? 8000 : 4000);
}

export async function guard<T>(work: Promise<T>): Promise<T | undefined> {
  try {
    return await work;
  } catch (e) {
    toast(errorText(e), "error");
    return undefined;
  }
}

export async function loadConfig() {
  app.config = await api.getConfig();
}

export async function saveConfig(config: Config) {
  app.config = await api.saveConfig(config);
  await refresh();
}

export async function refresh() {
  app.overview = (await guard(api.overview())) ?? app.overview;
  app.revision++;
}

// ---- jobs ------------------------------------------------------------------------

export type JobState = "queued" | "running" | "done" | "failed" | "cancelled";

export interface Job {
  key: number;
  spec: TaskSpec;
  title: string;
  state: JobState;
  id: number | null;
  command: string;
  lines: { stream: string; line: string }[];
  code: number | null;
  started: number | null;
  ended: number | null;
  /** Key of a job that must succeed first; this one is skipped otherwise. */
  requires: number | null;
}

export const jobs = $state({ list: [] as Job[], selected: null as number | null });

const MAX_LINES = 5000;
let jobKey = 0;
let listening = false;

export function enqueue(spec: TaskSpec, title: string, requires: Job | null = null): Job {
  const job: Job = {
    key: ++jobKey, spec, title, state: "queued", id: null, command: "", lines: [], code: null, started: null, ended: null,
    requires: requires?.key ?? null,
  };
  jobs.list.push(job);
  jobs.selected ??= job.key;
  void pump();
  return jobs.list[jobs.list.length - 1];
}

export const running = () => jobs.list.find((j) => j.state === "running") ?? null;
export const pending = () => jobs.list.filter((j) => j.state === "queued" || j.state === "running").length;

async function pump() {
  await listen();
  if (running()) return;
  const job = jobs.list.find((j) => j.state === "queued");
  if (!job) return;
  const before = jobs.list.find((j) => j.key === job.requires);
  if (before && before.state !== "done") {
    job.state = "cancelled";
    job.lines.push({ stream: "stderr", line: `skipped: "${before.title}" did not succeed` });
    return pump();
  }
  job.state = "running";
  job.started = Date.now();
  try {
    const started = await api.startTask(job.spec);
    job.id = started.id;
    job.title = started.title;
    job.command = started.command;
  } catch (e) {
    job.lines.push({ stream: "stderr", line: errorText(e) });
    finish(job, "failed", null);
  }
}

function finish(job: Job, state: JobState, code: number | null) {
  job.state = state;
  job.code = code;
  job.ended = Date.now();
  if (state === "failed") toast(`${job.title} failed`, "error");
  void refresh();
  void pump();
}

export function cancel(job: Job) {
  if (job.state === "queued") {
    job.state = "cancelled";
  } else if (job.state === "running" && job.id !== null) {
    void guard(api.cancelTask(job.id));
  }
}

export function clearFinished() {
  jobs.list = jobs.list.filter((j) => j.state === "queued" || j.state === "running");
  if (!jobs.list.some((j) => j.key === jobs.selected)) jobs.selected = jobs.list[0]?.key ?? null;
}

async function listen() {
  if (listening) return;
  listening = true;
  await onEvent<TaskOutput>("task-output", (o) => {
    const job = jobs.list.find((j) => j.id === o.id);
    if (!job) return;
    job.lines.push({ stream: o.stream, line: o.line });
    if (job.lines.length > MAX_LINES) job.lines.splice(0, job.lines.length - MAX_LINES);
  });
  await onEvent<TaskExit>("task-exit", (x) => {
    const job = jobs.list.find((j) => j.id === x.id);
    if (job) finish(job, x.cancelled ? "cancelled" : x.code === 0 ? "done" : "failed", x.code);
  });
}

// ---- formatting ------------------------------------------------------------------

export function ago(seconds: number | null): string {
  if (!seconds) return "";
  const d = Date.now() / 1000 - seconds;
  if (d < 60) return "just now";
  if (d < 3600) return `${Math.floor(d / 60)} min ago`;
  if (d < 86400) return `${Math.floor(d / 3600)} h ago`;
  return new Date(seconds * 1000).toLocaleDateString();
}

export function bytes(n: number | null): string {
  if (n === null) return "";
  if (n < 1024 * 1024) return `${(n / 1024).toFixed(0)} KB`;
  return `${(n / 1024 / 1024).toFixed(1)} MB`;
}

export function duration(job: Job): string {
  if (!job.started) return "";
  const s = ((job.ended ?? Date.now()) - job.started) / 1000;
  return s < 60 ? `${s.toFixed(1)} s` : `${Math.floor(s / 60)} min ${Math.round(s % 60)} s`;
}
