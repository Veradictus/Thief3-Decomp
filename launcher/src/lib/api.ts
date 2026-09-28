// Typed wrappers around the Rust commands (src-tauri/src). Outside Tauri, in a
// plain browser (`yarn dev`), calls go to mock.ts so the UI can be worked on
// and screenshotted without the game.
import { getVersion } from "@tauri-apps/api/app";
import { invoke } from "@tauri-apps/api/core";
import { listen, type UnlistenFn } from "@tauri-apps/api/event";
import { open } from "@tauri-apps/plugin-dialog";
import { mockCall, mockListen, mockPick } from "./mock";

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
  editsTime: number | null;
  patched: boolean;
  patchedTime: number | null;
  stale: boolean;
  installed: boolean;
  backedUp: boolean;
}

export interface ModEntry {
  name: string;
  enabled: boolean;
  size: number;
  modified: number | null;
}

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
  | { kind: "restore"; level: string | null };

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
  listMods: () => call<ModEntry[]>("list_mods"),
  setModEnabled: (name: string, enabled: boolean) => call<null>("set_mod_enabled", { name, enabled }),
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

export function errorText(e: unknown): string {
  return typeof e === "string" ? e : e instanceof Error ? e.message : JSON.stringify(e);
}
