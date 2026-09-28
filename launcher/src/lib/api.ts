// Typed wrappers around the Rust commands (src-tauri/src). Outside Tauri, in a
// plain browser (`yarn dev`), calls go to mock.ts so the UI can be worked on
// and screenshotted without the game.
import { getVersion } from "@tauri-apps/api/app";
import { invoke } from "@tauri-apps/api/core";
import { listen, type UnlistenFn } from "@tauri-apps/api/event";
import { getCurrentWebview } from "@tauri-apps/api/webview";
import { open, save } from "@tauri-apps/plugin-dialog";
import { mockCall, mockListen, mockPick, mockPickMods, mockPickSave } from "./mock";

export const inTauri = typeof window !== "undefined" && "__TAURI_INTERNALS__" in window;

export interface Config {
  gameDir: string | null;
  godot: string | null;
  python: string | null;
  sdkRoot: string | null;
  projectDir: string | null;
  setupComplete: boolean;
  /** The game's SaveGames folder; null: found automatically. */
  savesDir: string | null;
  backupBeforeLaunch: boolean;
  /** Look for launcher updates at start-up; null means yes. */
  autoUpdateCheck: boolean | null;
  lastUpdateCheck: number | null;
  /** The mod index the Mods page browses; null for the default. */
  modIndexUrl: string | null;
}

export interface Candidate {
  path: string;
  source: string;
}

export interface Detected {
  games: Candidate[];
  godots: Candidate[];
  pythons: Candidate[];
  sdkRoots: Candidate[];
}

export interface GameCheck {
  dir: string;
  ok: boolean;
  exeFound: boolean;
  sha1: string | null;
  supported: boolean;
  steam: boolean;
  maps: number;
  message: string;
}

export interface ToolCheck {
  path: string;
  ok: boolean;
  version: string | null;
  message: string;
}

export interface SdkRootCheck {
  path: string;
  ok: boolean;
  mapTools: boolean;
  packTools: boolean;
  sdkBuilt: boolean;
  message: string;
}

/** A path check as the settings fields show it. */
export interface CheckResult {
  ok: boolean;
  message: string;
  detail?: string;
}

export interface Overview {
  game: GameCheck | null;
  sdk: { installed: boolean; managed: boolean; built: boolean; buildable: boolean; settings: boolean };
  modsEnabled: number;
  modsDisabled: number;
  maps: { total: number; exported: number; edited: number; patched: number; installed: number };
  running: boolean;
}

export interface MapEntry {
  id: string;
  title: string | null;
  size: number | null;
  inGame: boolean;
  exported: boolean;
  actors: number | null;
  editedActors: number | null;
  /** Actors added or removed in Godot, which the edits file cannot save. */
  notSavedAdded: number;
  notSavedRemoved: number;
  editsTime: number | null;
  patched: boolean;
  patchedTime: number | null;
  stale: boolean;
  installed: boolean;
  backedUp: boolean;
}

// ---- mods (src-tauri/src/mods.rs; the format is docs/mods.md) ----

/** A DLL straight in System/mods (or System/mods/disabled when off). */
export interface LooseMod {
  name: string;
  enabled: boolean;
  size: number;
  modified: number | null;
}

/** An installed .t3mod package, System/mods/<id>/. */
export interface ModPackage {
  id: string;
  name: string;
  version: string | null;
  authors: string[];
  description: string | null;
  homepage: string | null;
  license: string | null;
  tags: string[];
  entry: string | null;
  api: number | null;
  requires: Record<string, string>;
  conflicts: string[];
  /** Switched on. */
  enabled: boolean;
  /** Enabled and without errors: loaded and applied. */
  active: boolean;
  position: number;
  size: number;
  /** Has a DLL. */
  code: boolean;
  /** Files under files/ and textures/. */
  files: number;
  textures: number;
  /** Why the package cannot be used. */
  error: string | null;
}

export type Severity = "error" | "warning" | "info";

export type FixAction =
  { kind: "moveBefore"; id: string; before: string } | { kind: "enable"; id: string } | { kind: "disable"; id: string };

export interface Issue {
  severity: Severity;
  /** The package it is about; null for the whole list. */
  mod: string | null;
  message: string;
  fix: { label: string; action: FixAction } | null;
}

export interface SyncReport {
  placed: number;
  restored: number;
  changed: string[];
  errors: string[];
  skipped: string[];
  installed: { id: string; name: string; version: string; previous: string | null } | null;
  removed: string | null;
}

export interface ModList {
  dir: string;
  /** In load order. */
  packages: ModPackage[];
  loose: LooseMod[];
  profile: string;
  profiles: string[];
  issues: Issue[];
  sdk: { installed: boolean; api: number };
  /**
   * t3texpack.py: `needed` when the enabled texture packs (`mods`, in load
   * order) changed; `bundles` are game bundles (.ibt) that wait for a
   * `restore` before the sync places or removes them.
   */
  textures: { needed: boolean; mods: string[]; bundles: string[] };
  report: SyncReport | null;
}

export type ProfileAction =
  | { kind: "saveAs"; name: string }
  | { kind: "switch"; name: string }
  | { kind: "delete"; name: string }
  | { kind: "rename"; from: string; to: string };

export interface IndexNote {
  severity: Severity;
  message: string;
}

export interface IndexVersion {
  version: string;
  url: string;
  size: number;
  released: string | null;
  api: number | null;
  requires: Record<string, string>;
  conflicts: string[];
  /** No errors: it can be installed next to the enabled mods. */
  compatible: boolean;
  notes: IndexNote[];
}

export interface IndexMod {
  id: string;
  name: string;
  description: string | null;
  authors: string[];
  homepage: string | null;
  license: string | null;
  tags: string[];
  installed: string | null;
  enabled: boolean;
  /** Newest first. */
  versions: IndexVersion[];
  recommended: string | null;
}

export interface ModIndex {
  url: string;
  generated: string | null;
  skipped: number;
  mods: IndexMod[];
  updates: { id: string; name: string; installed: string; latest: string }[];
}

export interface DownloadProgress {
  id: string;
  received: number;
  total: number;
}

/** Files dragged over or dropped onto the window. */
export type FileDrop = { type: "enter" | "drop"; paths: string[] } | { type: "over" | "leave" };

export interface Setting {
  key: string;
  value: string;
  default: string | null;
  description: string;
}

export interface SdkSettings {
  file: string;
  exists: boolean;
  template: string | null;
  sections: { name: string; settings: Setting[] }[];
}

export type TaskSpec =
  | { kind: "sdkBuild" }
  | { kind: "sdkDeploy" }
  | { kind: "sdkUndeploy" }
  | { kind: "export"; level: string | null }
  | { kind: "import" }
  | { kind: "godotCheck" }
  | { kind: "roundtrip"; level: string | null }
  | { kind: "repack"; level: string }
  | { kind: "install"; level: string }
  | { kind: "restore"; level: string | null }
  | { kind: "texturePacks"; mods: string[] }
  | { kind: "textureRestore" };

export interface TaskStarted {
  id: number;
  title: string;
  command: string;
}

export interface TaskOutput {
  id: number;
  stream: "stdout" | "stderr";
  line: string;
}

export interface TaskExit {
  id: number;
  code: number | null;
  cancelled: boolean;
}

export interface SavesFolder {
  path: string;
  source: string;
  exists: boolean;
}

export interface SavesSummary {
  count: number;
  files: number;
  size: number;
  newest: number | null;
}

export interface SavesInfo {
  folder: SavesFolder | null;
  exists: boolean;
  summary: SavesSummary;
  candidates: SavesFolder[];
}

export interface Backup {
  file: string;
  label: string | null;
  created: number;
  saves: number | null;
  size: number | null;
  bytes: number;
}

export interface BackupList {
  dir: string;
  backups: Backup[];
}

export interface Restored {
  before: Backup | null;
  summary: SavesSummary;
}

export interface LogsReport {
  path: string;
  files: number;
  bytes: number;
}

export interface UpdaterStatus {
  /** This build can update itself (it was built with the update key). */
  enabled: boolean;
  /** Unzipped from the portable zip: new versions are downloaded by hand. */
  portable: boolean;
  version: string;
  lastCheck: number | null;
}

export interface UpdateInfo {
  version: string;
  currentVersion: string;
  notes: string | null;
  /** Release date, Unix seconds. */
  date: number | null;
}

export interface UpdateCheck {
  /** False when the start-up check was skipped (turned off, or done today). */
  checked: boolean;
  update: UpdateInfo | null;
}

export interface UpdateProgress {
  downloaded: number;
  total: number | null;
  finished: boolean;
}

/** Before the real config loads (the UI waits for it, so this is rarely seen). */
export const emptyConfig: Config = {
  gameDir: null,
  godot: null,
  python: null,
  sdkRoot: null,
  projectDir: null,
  setupComplete: false,
  savesDir: null,
  backupBeforeLaunch: false,
  autoUpdateCheck: null,
  lastUpdateCheck: null,
  modIndexUrl: null,
};

export type Location = "game" | "system" | "mods" | "log" | "project" | "sdk" | "patched" | "backup";

function call<T>(cmd: string, args?: Record<string, unknown>): Promise<T> {
  return inTauri ? invoke<T>(cmd, args) : (mockCall(cmd, args) as Promise<T>);
}

export const api = {
  getConfig: () => call<Config>("get_config"),
  saveConfig: (config: Config) => call<Config>("save_config", { config }),
  detectAll: () => call<Detected>("detect_all"),
  checkGame: (path: string) => call<GameCheck>("check_game", { path }),
  checkGodot: (path: string) => call<ToolCheck>("check_godot", { path }),
  checkPython: (path: string) => call<ToolCheck>("check_python", { path }),
  checkSdkRoot: (path: string) => call<SdkRootCheck>("check_sdk_root", { path }),
  overview: () => call<Overview>("overview"),
  listMaps: () => call<MapEntry[]>("list_maps"),
  listMods: () => call<ModList>("list_mods"),
  /** A loose DLL on or off. */
  setModEnabled: (name: string, enabled: boolean) => call<ModList>("set_mod_enabled", { name, enabled }),
  setPackageEnabled: (id: string, enabled: boolean) => call<ModList>("set_package_enabled", { id, enabled }),
  setModOrder: (order: string[]) => call<ModList>("set_mod_order", { order }),
  installMod: (path: string) => call<ModList>("install_mod", { path }),
  removeMod: (id: string) => call<ModList>("remove_mod", { id }),
  syncMods: () => call<ModList>("sync_mods"),
  modProfile: (action: ProfileAction) => call<ModList>("mod_profile", { action }),
  modIndex: (refresh: boolean) => call<ModIndex>("mod_index", { refresh }),
  installFromIndex: (id: string, version: string) => call<ModList>("install_from_index", { id, version }),
  readSdkSettings: () => call<SdkSettings>("read_sdk_settings"),
  writeSdkSettings: (changes: { section: string; key: string; value: string }[]) =>
    call<null>("write_sdk_settings", { changes }),
  createSdkSettings: () => call<null>("create_sdk_settings"),
  readSdkLog: (lines: number) => call<string[]>("read_sdk_log", { lines }),
  launchGame: () => call<string>("launch_game"),
  openGodot: (level: string | null, editor: boolean) => call<null>("open_godot", { level, editor }),
  openLocation: (which: Location) => call<null>("open_location", { which }),
  openLink: (url: string) => call<null>("open_link", { url }),
  startTask: (spec: TaskSpec) => call<TaskStarted>("start_task", { spec }),
  cancelTask: (id: number) => call<null>("cancel_task", { id }),
  savesInfo: (path: string | null = null) => call<SavesInfo>("saves_info", { path }),
  listSaveBackups: () => call<BackupList>("list_save_backups"),
  createSaveBackup: (label: string | null) => call<Backup>("create_save_backup", { label }),
  restoreSaveBackup: (file: string) => call<Restored>("restore_save_backup", { file }),
  deleteSaveBackup: (file: string) => call<null>("delete_save_backup", { file }),
  openSavesFolder: (which: "saves" | "backups") => call<null>("open_saves_folder", { which }),
  collectLogs: (path: string, tasks: string | null) => call<LogsReport>("collect_logs", { path, tasks }),
  updaterStatus: () => call<UpdaterStatus>("updater_status"),
  checkUpdate: (auto: boolean) => call<UpdateCheck>("check_update", { auto }),
  installUpdate: () => call<null>("install_update"),
};

/** The launcher's version ("preview" outside Tauri). */
export function launcherVersion(): Promise<string> {
  return inTauri ? getVersion() : Promise.resolve("preview");
}

// The caller names the payload type the Rust side emits, as with Tauri's listen().
// eslint-disable-next-line @typescript-eslint/no-unnecessary-type-parameters
export function onEvent<T>(name: string, handler: (payload: T) => void): Promise<UnlistenFn> {
  if (!inTauri)
    return mockListen(name, (payload) => {
      handler(payload as T);
    });
  return listen<T>(name, (e) => {
    handler(e.payload);
  });
}

/** A folder or file picker; null when cancelled. */
export async function pick(directory: boolean, title: string): Promise<string | null> {
  if (!inTauri) return mockPick(directory, title);
  const chosen = await open({ directory, multiple: false, title });
  return typeof chosen === "string" ? chosen : null;
}

/** .t3mod files to install; empty when cancelled. */
export async function pickModPackages(): Promise<string[]> {
  if (!inTauri) return mockPickMods();
  const chosen = await open({
    multiple: true,
    title: "Install mods",
    filters: [{ name: "T3SDK mod package", extensions: ["t3mod"] }],
  });
  return chosen ?? [];
}

/** Files dragged onto the window (Tauri's drag and drop; nothing in a browser). */
export function onFileDrop(handler: (event: FileDrop) => void): Promise<UnlistenFn> {
  if (!inTauri) return Promise.resolve(() => undefined);
  return getCurrentWebview().onDragDropEvent((e) => {
    const p = e.payload;
    handler(p.type === "enter" || p.type === "drop" ? { type: p.type, paths: p.paths } : { type: p.type });
  });
}

/** A save dialog for a .zip file; null when cancelled. */
export async function pickZip(title: string, defaultPath: string): Promise<string | null> {
  if (!inTauri) return mockPickSave(title, defaultPath);
  return await save({ title, defaultPath, filters: [{ name: "Zip archive", extensions: ["zip"] }] });
}

export function errorText(e: unknown): string {
  return typeof e === "string" ? e : e instanceof Error ? e.message : JSON.stringify(e);
}
