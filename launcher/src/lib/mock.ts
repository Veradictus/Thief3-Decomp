// Stand-in for the Rust side when the UI runs in a plain browser (`yarn dev`):
// made-up data, no files touched. Lets the UI be developed, tested and
// screenshotted without Tauri, the game or Godot.
import type {
  Backup,
  Config,
  Detected,
  GameCheck,
  MapEntry,
  Overview,
  SavesInfo,
  SdkSettings,
  Setting,
  TaskSpec,
  TaskStarted,
} from "./api";
import { mockMods } from "./mock-mods";

type Handler = (payload: unknown) => void;
type Args = Record<string, unknown>;

const handlers = new Map<string, Set<Handler>>();
const params = new URLSearchParams(typeof location === "undefined" ? "" : location.search);
const firstRun = params.has("setup");

let config: Config = {
  gameDir: firstRun ? null : "D:\\SteamLibrary\\steamapps\\common\\Thief Deadly Shadows",
  godot: firstRun ? null : "C:\\Tools\\Godot\\Godot_v4.7.2-stable_win64.exe",
  python: firstRun ? null : "C:\\Dev\\Thief3-Decomp\\.venv\\Scripts\\python.exe",
  sdkRoot: firstRun ? null : "C:\\Dev\\Thief3-Decomp",
  projectDir: null,
  setupComplete: !firstRun,
  savesDir: null,
  backupBeforeLaunch: false,
  autoUpdateCheck: null,
  lastUpdateCheck: null,
  modIndexUrl: null,
};

type SettingRow = [section: string, key: string, value: string, description: string];
const settings: (Setting & { section: string })[] = (
  [
    ["T3SDK", "Console", "0", "1 = open a console window that shows T3SDK.log live."],
    ["T3SDK", "EngineLog", "1", "1 = copy the engine's own log (GLog) into T3SDK.log."],
    [
      "T3SDK",
      "DumpObjectsKey",
      "0x79",
      "Virtual-key code that writes every live object to T3SDK_objects.txt while the game has focus (0x79 = F10, 0 = off).",
    ],
    ["T3SDK", "MenuVersionLabel", "1", '1 = add "[Modded - T3SDK <version>]" to the main menu\'s version line.'],
    ["T3SDK", "MenuInputTrace", "0", "1 = log main-menu and popup input events (diagnostics)."],
    ["Fixes", "SkipIntros", "1", "1 = skip the Eidos, Ion Storm, copyright, nVidia and EAX logo movies at start-up."],
    [
      "Display",
      "NativeResolutions",
      "1",
      "1 = offer the monitor's own resolutions in Options > Audio/Video; the highest setting is the native resolution (the game only knows 640x480 to 1600x1200).",
    ],
    [
      "Display",
      "Borderless",
      "1",
      "1 = borderless window covering the monitor instead of exclusive fullscreen: alt-tab, other monitors and screenshots work.",
    ],
    [
      "Display",
      "WidescreenUI",
      "1",
      "1 = lay menus and HUD out for the monitor's aspect ratio instead of stretching 4:3: menus stay centered, the HUD moves out to the screen edges.",
    ],
    [
      "Display",
      "UILayoutTrace",
      "0",
      "1 = log where each UI window is placed (for UI modding; T3UI.ini defines them).",
    ],
    [
      "Display",
      "PauseInBackground",
      "0",
      "1 = pause while another window has the focus, as the game does on its own. 0 = a borderless game keeps running in the background.",
    ],
    [
      "Display",
      "SmoothFrames",
      "1",
      "1 = move the game world on every frame. The engine moves it only once 10 ms have passed, so above 100 fps the world and the camera move on every second or third frame and the game looks choppy however high the frame rate is.",
    ],
    [
      "Display",
      "MaxFPS",
      "0",
      "Highest frame rate, 0 = no limit. The game's own VSynch option (Options > Audio/Video, on by default) also works in a borderless window: one frame per monitor refresh.",
    ],
    [
      "Display",
      "CursorScale",
      "0",
      "Size of the menu cursor in a borderless window: 0 = grow with the screen height (1x at 768 lines), or a fixed factor such as 1.5.",
    ],
    ["Display", "FrameStats", "0", "1 = log frames per second and the time spent presenting frames, every 10 s."],
  ] satisfies SettingRow[]
).map(([section, key, value, description]) => ({ section, key, value, default: value, description }));

const now = Math.floor(Date.now() / 1000);
type MapRow = [
  id: string,
  title: string,
  actors: number,
  exported: boolean,
  edited: number | null,
  editsTime: number | null,
  patched: boolean,
  patchedTime: number | null,
  installed: boolean,
];
// The game's own maps and level titles, sorted as the launcher lists them
// (by title once exported, by file name before).
const mapRows: MapRow[] = [
  ["Auldale1", "Auldale", 2371, true, 4, now - 3600, true, now - 3000, true],
  ["Castle1", "Castle Front", 2113, true, null, null, false, null, false],
  ["HammerIntro1", "Cathedral Grounds", 2916, true, null, null, false, null, false],
  ["dungeon2", "Citadel Core", 1366, true, null, null, false, null, false],
  ["docks2", "Docks", 3101, true, 12, now - 600, true, now - 5400, false],
  ["Entry", "Entry", 21, true, null, null, false, null, false],
  ["OldQuarter3", "Fort Ironwood", 2414, true, null, null, false, null, false],
  ["Auldale3", "Gamall's Lair", 1805, true, null, null, false, null, false],
  ["SouthQuarter1_int1", "Garrett's Building", 780, true, null, null, false, null, false],
  ["HammerIntro2", "Hammer Factory", 1740, true, null, null, false, null, false],
  ["HauntedHouse1", "Outer Cradle", 3694, false, null, null, false, null, false],
  ["HauntedHouse2", "Inner Cradle", 3949, false, null, null, false, null, false],
  ["Castle2", "Inner Quarters", 2215, true, null, null, false, null, false],
  ["KeeperCompound1", "Keeper Compound", 2502, false, null, null, false, null, false],
  ["KeeperCompound2", "Lower Libraries", 1260, false, null, null, false, null, false],
  ["Clocktower2", "Lower Clocktower", 2370, true, null, null, false, null, false],
  ["museum2", "Tesero Hall", 2631, false, null, null, false, null, false],
  ["OldQuarter1", "Old Quarter", 2659, false, null, null, false, null, false],
  ["dungeon1", "Outer Citadel", 1397, true, null, null, false, null, false],
  ["PaganIntro1", "Pagan Tunnels", 1603, false, null, null, false, null, false],
  ["PaganIntro2", "Pagan Sanctuary", 3158, false, null, null, false, null, false],
  ["museum1", "Porter Hall", 2931, true, null, null, false, null, false],
  ["SeasideMansion1", "Overlook Grounds", 2770, false, null, null, false, null, false],
  ["SeasideMansion2", "Overlook Proper", 2583, false, null, null, false, null, false],
  ["SouthQuarter1", "South Quarter", 2868, false, null, null, false, null, false],
  ["SouthQuarter3", "Pavelock Prison", 2006, false, null, null, false, null, false],
  ["Stonemarket1", "Stonemarket Plaza", 2883, true, null, null, false, null, false],
  ["Stonemarket2", "Stonemarket Proper", 2649, false, null, null, false, null, false],
  ["Stonemarket3", "Keeper Library", 2679, false, null, null, false, null, false],
  ["docks3", "The Abysmal Gale", 1904, true, null, null, false, null, false],
  ["Inn", "The Blue Heron Inn", 2526, true, 2, now - 7200, false, null, false],
  ["Clocktower1", "Upper Clocktower", 2299, true, null, null, false, null, false],
];
// Exported by older tools: Map Studio updates them before opening them.
const olderExports = new Set(["Castle1", "Inn", "docks3"]);
const maps: MapEntry[] = mapRows.map(
  ([id, title, actors, exported, edited, editsTime, patched, patchedTime, installed]) => ({
    id,
    title: exported ? title : null,
    size: actors * 9100,
    inGame: true,
    exported,
    outdated: exported && olderExports.has(id),
    actors: exported ? actors : null,
    editedActors: edited,
    notSaved: 0,
    editsTime,
    patched,
    patchedTime,
    stale: editsTime !== null && patchedTime !== null && editsTime > patchedTime,
    installed,
    backedUp: installed,
  }),
);

const game = (): GameCheck => ({
  dir: config.gameDir ?? "",
  ok: true,
  exeFound: true,
  sha1: "40bf68a54246bcde2fb5fcbc75b94dc7c7f78305",
  supported: true,
  steam: true,
  maps: maps.length,
  message: `Steam release, patch 1.1: supported. ${maps.length} maps.`,
});

// Lines in the formats the SDK writes (sdk.cpp, display.cpp).
const log = [
  "[12:01:07.214] T3SDK 0.4.0 in C:\\...\\System\\T3Main.exe",
  "[12:01:07.216] fixes: skip intros on",
  "[12:01:07.231] display: resolutions 1280x720, 1600x900, 1920x1080, 2048x1152, 2560x1440 (option 4 = native)",
  "[12:01:07.233] display: native resolutions on, borderless on, widescreen UI on (width 852), keeps running in the background",
  "[12:01:07.233] display: smooth frames on, no frame limit",
  "[12:01:07.260] hooks: frame ok, exit ok, engine log ok, menu version label ok, menu input trace off",
  "[12:01:07.262] mods: loaded hello.dll",
  "[12:01:07.263] started; waiting for the engine",
  "[12:01:07.912] display: UI layout width 640 -> 852",
  "[12:01:08.901] object layout validated: 4488 objects, 287 classes, Outer at 0x18, SuperField at 0x2C (287/287 classes reach Object)",
  "[12:01:08.902] engine ready",
  "[12:01:08.940] [hello] engine ready: 4488 objects",
  "[12:01:11.371] display: CreateDevice 2560x1440 fullscreen made borderless, VSync -> 0x00000000",
  "[12:01:11.377] display: window brought to the front",
  "[12:01:11.402] display: cursor 32x32 shown at x1.88",
];

// Saves and their backups.
const savesPath = "C:\\Users\\Public\\Documents\\Thief - Deadly Shadows\\SaveGames";
const savesInfo = (): SavesInfo => ({
  folder: {
    path: config.savesDir ?? savesPath,
    source: config.savesDir ? "Settings" : "Public Documents",
    exists: true,
  },
  exists: true,
  summary: { count: 7, files: 96, size: 48_600_000, newest: now - 5400 },
  candidates: [
    { path: savesPath, source: "Public Documents", exists: true },
    { path: "D:\\Documents\\Thief - Deadly Shadows\\SaveGames", source: "Documents", exists: false },
  ],
});
type BackupRow = [created: number, label: string | null, saves: number];
const backups: Backup[] = (
  [
    [now - 86400, "before the Cathedral", 6],
    [now - 3 * 86400, "before launch", 5],
    [now - 9 * 86400, null, 3],
  ] satisfies BackupRow[]
).map(([created, label, saves]) => backup(created, label, saves));

function backup(created: number, label: string | null, saves: number): Backup {
  const d = new Date(created * 1000);
  const pad = (n: number) => n.toString().padStart(2, "0");
  const stamp = `${d.getFullYear().toString()}-${pad(d.getMonth() + 1)}-${pad(d.getDate())}_${pad(d.getHours())}${pad(d.getMinutes())}${pad(d.getSeconds())}`;
  const size = saves * 6_900_000;
  return {
    file: `${stamp}${label ? ` ${label}` : ""}.zip`,
    label,
    created,
    saves,
    size,
    bytes: Math.round(size * 0.62),
  };
}

function fakeInstall() {
  const total = 9_400_000;
  for (let i = 1; i <= 10; i++) {
    setTimeout(() => {
      emit("update-progress", { downloaded: (total * i) / 10, total, finished: false });
    }, 150 * i);
  }
  return new Promise((resolve) =>
    setTimeout(() => {
      emit("update-progress", { downloaded: 0, total: null, finished: true });
      resolve(null);
    }, 1700),
  );
}

function emit(name: string, payload: unknown) {
  handlers.get(name)?.forEach((h) => {
    h(payload);
  });
}

const mods = mockMods(emit);

let nextTask = 1;
function fakeTask(title: string): TaskStarted {
  const id = nextTask++;
  const lines = [
    `+ python ${title.toLowerCase().replace(/ /g, "_")}.py`,
    "reading package tables...",
    "1412 actors -> Inn/Inn.actors.json (0.8 s)",
    "  96 mesh/skin pairs exported, 0 meshes not found in the bundles (6.1 s)",
    "  BSP: Inn_bsp.glb (7.9 s)",
    "  scene: Inn/Inn.tscn  (The Inn)",
  ];
  lines.forEach((line, i) => {
    setTimeout(
      () => {
        emit("task-output", { id, stream: "stdout", line });
      },
      250 * (i + 1),
    );
  });
  setTimeout(
    () => {
      emit("task-exit", { id, code: 0, cancelled: false });
    },
    250 * (lines.length + 1),
  );
  return { id, title, command: `python tools/... (${title})` };
}

export function taskTitle(spec: TaskSpec): string {
  const level = "level" in spec ? (spec.level ?? "all maps") : "";
  switch (spec.kind) {
    case "sdkBuild":
      return "Build T3SDK";
    case "sdkDeploy":
      return "Install T3SDK";
    case "sdkUndeploy":
      return "Remove T3SDK";
    case "export":
      return `Export ${level}`;
    case "import":
      return "Import into Godot";
    case "godotCheck":
      return "Check the Godot project";
    case "roundtrip":
      return `Round-trip check: ${level}`;
    case "repack":
      return `Repack ${level}`;
    case "install":
      return `Install ${level}`;
    case "restore":
      return `Restore ${level}`;
    case "texturePacks":
      return spec.mods.length ? `Apply texture packs: ${spec.mods.join(", ")}` : "Restore the original textures";
    case "textureRestore":
      return "Restore the game's bundles, then place the mods' bundles";
  }
}

function text(args: Args, key: string): string {
  const value = args[key];
  if (typeof value !== "string") throw new Error(`mock: ${key} must be a string`);
  return value;
}

function sdkSettings(): SdkSettings {
  const sections: SdkSettings["sections"] = [];
  for (const { section, ...setting } of settings) {
    let found = sections.find((x) => x.name === section);
    if (!found) sections.push((found = { name: section, settings: [] }));
    found.settings.push({ ...setting });
  }
  return { file: "...\\System\\T3SDK.ini", exists: true, template: "...\\sdk\\T3SDK.ini", sections };
}

const commands: Record<string, (args: Args) => unknown> = {
  get_config: () => ({ ...config }),
  save_config: (args) => {
    config = { ...(args.config as Config) };
    return { ...config };
  },
  detect_all: (): Detected => ({
    games: [{ path: "D:\\SteamLibrary\\steamapps\\common\\Thief Deadly Shadows", source: "Steam library" }],
    godots: [{ path: "C:\\Tools\\Godot\\Godot_v4.7.2-stable_win64.exe", source: "user folder" }],
    pythons: [
      { path: "C:\\Dev\\Thief3-Decomp\\.venv\\Scripts\\python.exe", source: "T3SDK .venv" },
      { path: "C:\\Python312\\python.exe", source: "py launcher" },
    ],
    sdkRoots: [{ path: "C:\\Dev\\Thief3-Decomp", source: "next to the launcher" }],
  }),
  check_game: (args) => ({ ...game(), dir: text(args, "path") }),
  check_godot: (args) => ({ path: text(args, "path"), ok: true, version: "4.7.2.stable.official", message: "Ready." }),
  check_python: (args) => ({ path: text(args, "path"), ok: true, version: "3.12.4", message: "Ready." }),
  check_sdk_root: (args) => ({
    path: text(args, "path"),
    ok: true,
    mapTools: true,
    packTools: true,
    sdkBuilt: true,
    message: "Ready.",
  }),
  overview: (): Overview => ({
    game: config.gameDir ? game() : null,
    sdk: { installed: true, managed: true, built: true, buildable: true, settings: true },
    modsEnabled: mods.counts().on,
    modsDisabled: mods.counts().off,
    maps: {
      total: maps.length,
      exported: maps.filter((m) => m.exported).length,
      edited: maps.filter((m) => m.editedActors).length,
      patched: maps.filter((m) => m.patched).length,
      installed: maps.filter((m) => m.installed).length,
    },
    running: false,
  }),
  list_maps: () => maps.map((m) => ({ ...m })),
  ...mods.commands,
  read_sdk_settings: sdkSettings,
  write_sdk_settings: (args) => {
    for (const change of args.changes as { section: string; key: string; value: string }[]) {
      const setting = settings.find((s) => s.section === change.section && s.key === change.key);
      if (setting) setting.value = change.value;
    }
    return null;
  },
  create_sdk_settings: () => null,
  read_sdk_log: (args) => log.slice(-Number(args.lines)),
  launch_game: () => "Asked Steam to start the game.",
  open_godot: () => null,
  open_location: () => null,
  open_link: () => null,
  cancel_task: () => null,
  start_task: (args) => {
    const spec = args.spec as TaskSpec;
    if (spec.kind === "texturePacks") mods.texturesApplied(spec.mods);
    if (spec.kind === "export") {
      for (const m of maps) if (spec.level === null || m.id === spec.level) m.outdated = false;
    }
    return fakeTask(taskTitle(spec));
  },
  saves_info: (args) =>
    typeof args.path === "string"
      ? { ...savesInfo(), folder: { path: args.path, source: "Settings", exists: true } }
      : savesInfo(),
  list_save_backups: () => ({ dir: "...\\org.t3sdk.launcher\\saves", backups: backups.map((b) => ({ ...b })) }),
  create_save_backup: (args) => {
    const made = backup(Math.floor(Date.now() / 1000), typeof args.label === "string" ? args.label : null, 7);
    backups.unshift(made);
    return { ...made };
  },
  restore_save_backup: () => {
    const before = backup(Math.floor(Date.now() / 1000), "before restore", 7);
    backups.unshift(before);
    return { before: { ...before }, summary: savesInfo().summary };
  },
  delete_save_backup: (args) => {
    const i = backups.findIndex((b) => b.file === text(args, "file"));
    if (i < 0) throw new Error("mock: no such backup");
    backups.splice(i, 1);
    return null;
  },
  open_saves_folder: () => null,
  collect_logs: (args) => ({ path: text(args, "path"), files: 11, bytes: 182_000 }),
  updater_status: () => ({ enabled: true, portable: false, version: "0.1.0", lastCheck: config.lastUpdateCheck }),
  // `?update` makes the check find a new version.
  check_update: () => {
    config.lastUpdateCheck = Math.floor(Date.now() / 1000);
    const update = params.has("update")
      ? {
          version: "0.2.0",
          currentVersion: "0.1.0",
          notes: "T3SDK Launcher 0.2.0: https://github.com/Veradictus/Thief3-Decomp/releases/tag/v0.2.0",
          date: now - 7200,
        }
      : null;
    return { checked: true, update };
  },
  install_update: fakeInstall,
};

export async function mockCall(cmd: string, args: Args = {}): Promise<unknown> {
  await new Promise((resolve) => setTimeout(resolve, 60));
  const command = commands[cmd];
  if (!command) throw new Error(`mock: unknown command ${cmd}`);
  return command(args);
}

export function mockListen(name: string, handler: Handler): Promise<() => void> {
  let set = handlers.get(name);
  if (!set) handlers.set(name, (set = new Set()));
  set.add(handler);
  return Promise.resolve(() => {
    set.delete(handler);
  });
}

export function mockPick(directory: boolean, title: string): Promise<string | null> {
  return Promise.resolve(window.prompt(`${title} (${directory ? "folder" : "file"} path)`));
}

export function mockPickMods(): Promise<string[]> {
  const path = window.prompt("Install mods (.t3mod path)", "C:\\Downloads\\night-vision-1.0.0.t3mod");
  return Promise.resolve(path ? [path] : []);
}

export function mockPickSave(title: string, defaultPath: string): Promise<string | null> {
  return Promise.resolve(window.prompt(`${title} (file path)`, defaultPath));
}
