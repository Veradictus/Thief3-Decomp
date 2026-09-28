// Shared UI state: the config, the status overview, navigation, toasts, and the
// job queue. Jobs run one at a time, in order, so two tools never write the
// same Godot project or game folder at once.
import {
  api,
  errorText,
  onEvent,
  type Config,
  type Overview,
  type TaskExit,
  type TaskOutput,
  type TaskSpec,
} from "./api";
import { elapsed } from "./format";

export type Page = "play" | "maps" | "mods" | "saves" | "sdk" | "tasks" | "settings";

interface AppState {
  config: Config | null;
  overview: Overview | null;
  page: Page;
  toasts: { id: number; text: string; kind: "info" | "error" }[];
  /** Bumped when files may have changed, so pages reload their lists. */
  revision: number;
}

export const app = $state<AppState>({ config: null, overview: null, page: "play", toasts: [], revision: 0 });

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
  /** Runs once this job has succeeded, e.g. to open what it prepared. */
  onDone: (() => void) | null;
}

export const jobs = $state({ list: [] as Job[], selected: null as number | null });

const MAX_LINES = 5000;
let jobKey = 0;
let listening = false;

export function enqueue(
  spec: TaskSpec,
  title: string,
  requires: Job | null = null,
  onDone: (() => void) | null = null,
): Job {
  const job: Job = {
    key: ++jobKey,
    spec,
    title,
    state: "queued",
    id: null,
    command: "",
    lines: [],
    code: null,
    started: null,
    ended: null,
    requires: requires?.key ?? null,
    onDone,
  };
  jobs.list.push(job);
  jobs.selected ??= job.key;
  void pump();
  // The stored copy is the reactive one: return it, not the plain object.
  return jobs.list.find((j) => j.key === job.key) ?? job;
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
  if (state === "done") job.onDone?.();
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

export function duration(job: Job): string {
  return elapsed(job.started, job.ended);
}
