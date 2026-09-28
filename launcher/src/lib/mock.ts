// Stand-in for the Rust side when the UI runs in a plain browser (`yarn dev`):
// made-up data, no files touched. Lets the UI be developed, tested and
// screenshotted without Tauri, the game or Godot.
import type {
  Config,
  Detected,
  GameCheck,
  MapEntry,
  ModEntry,
  Overview,
  SdkSettings,
  Setting,
  TaskSpec,
  TaskStarted,
} from "./api";

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
};

const mods: ModEntry[] = [
  { name: "hello", enabled: true, size: 14336, modified: 1790000000 },
  { name: "coop_prototype", enabled: false, size: 188416, modified: 1790100000 },
];

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
      "1 = offer the monitor's own resolutions in Options > Audio/Video; the highest setting is the native resolution.",
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
      "1 = lay menus and HUD out for the monitor's aspect ratio instead of stretching 4:3.",
    ],
    [
      "Display",
      "UILayoutTrace",
      "0",
      "1 = log where each UI window is placed (for UI modding; T3UI.ini defines them).",
    ],
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
const mapRows: MapRow[] = [
  ["Inn", "The Inn", 1412, true, 3, now - 3600, true, now - 3000, true],
  ["Docks", "The Docks", 2210, true, 12, now - 600, true, now - 5400, false],
  ["Museum", "The Museum", 1893, true, null, null, false, null, false],
  ["Cathedral", "The Cathedral", 2604, true, null, null, false, null, false],
  ["Keep", "The Keep", 1720, false, null, null, false, null, false],
  ["Manor", "The Manor", 1508, false, null, null, false, null, false],
  ["Lighthouse", "The Lighthouse", 980, false, null, null, false, null, false],
  ["Clocktower", "The Clocktower", 1311, false, null, null, false, null, false],
  ["Entry", "Main menu", 212, true, null, null, false, null, false],
];
const maps: MapEntry[] = mapRows.map(
  ([id, title, actors, exported, edited, editsTime, patched, patchedTime, installed]) => ({
    id,
    title: exported ? title : null,
    size: actors * 9100,
    inGame: true,
    exported,
    actors: exported ? actors : null,
    editedActors: edited,
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

const log = [
  "[12:01:07.214] T3SDK 0.4.0 in C:\\...\\System\\T3Main.exe",
  "[12:01:07.260] hooks: frame ok, exit ok, engine log ok, menu version label ok, menu input trace off",
  "[12:01:07.262] mods: loaded hello.dll",
  "[12:01:07.263] started; waiting for the engine",
  "[12:01:08.901] object layout validated: 4488 objects, 287 classes, Outer at 0x18, SuperField at 0x2C (287/287 classes reach Object)",
  "[12:01:08.902] engine ready",
  "[12:01:08.940] [hello] engine ready: 4488 objects",
  "[12:01:11.377] display: borderless 2560x1440 on monitor 1",
];

function emit(name: string, payload: unknown) {
  handlers.get(name)?.forEach((h) => {
    h(payload);
  });
}

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
    modsEnabled: mods.filter((m) => m.enabled).length,
    modsDisabled: mods.filter((m) => !m.enabled).length,
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
  list_mods: () => mods.map((m) => ({ ...m })),
  set_mod_enabled: (args) => {
    const mod = mods.find((m) => m.name === text(args, "name"));
    if (!mod) throw new Error("mock: no such mod");
    mod.enabled = args.enabled === true;
    return null;
  },
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
  start_task: (args) => fakeTask(taskTitle(args.spec as TaskSpec)),
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
