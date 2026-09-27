// Stand-in for the Rust side when the UI runs in a plain browser (`npm run
// dev`): made-up data, no files touched. Lets the UI be developed and
// screenshotted without Tauri, the game or Godot.
type Handler = (payload: any) => void;

const handlers = new Map<string, Set<Handler>>();
const params = new URLSearchParams(typeof location !== "undefined" ? location.search : "");
const firstRun = params.has("setup");

const state = {
  config: {
    gameDir: firstRun ? null : "D:\\SteamLibrary\\steamapps\\common\\Thief Deadly Shadows",
    godot: firstRun ? null : "C:\\Tools\\Godot\\Godot_v4.7.2-stable_win64.exe",
    python: firstRun ? null : "C:\\Dev\\Thief3-Decomp\\.venv\\Scripts\\python.exe",
    sdkRoot: firstRun ? null : "C:\\Dev\\Thief3-Decomp",
    projectDir: null as string | null,
    setupComplete: !firstRun,
  },
  mods: [
    { name: "hello", enabled: true, size: 14336, modified: 1790000000 },
    { name: "coop_prototype", enabled: false, size: 188416, modified: 1790100000 },
  ],
  settings: [
    ["T3SDK", "Console", "0", "1 = open a console window that shows T3SDK.log live."],
    ["T3SDK", "EngineLog", "1", "1 = copy the engine's own log (GLog) into T3SDK.log."],
    ["T3SDK", "DumpObjectsKey", "0x79", "Virtual-key code that writes every live object to T3SDK_objects.txt while the game has focus (0x79 = F10, 0 = off)."],
    ["T3SDK", "MenuVersionLabel", "1", "1 = add \"[Modded - T3SDK <version>]\" to the main menu's version line."],
    ["T3SDK", "MenuInputTrace", "0", "1 = log main-menu and popup input events (diagnostics)."],
    ["Fixes", "SkipIntros", "1", "1 = skip the Eidos, Ion Storm, copyright, nVidia and EAX logo movies at start-up."],
    ["Display", "NativeResolutions", "1", "1 = offer the monitor's own resolutions in Options > Audio/Video; the highest setting is the native resolution."],
    ["Display", "Borderless", "1", "1 = borderless window covering the monitor instead of exclusive fullscreen: alt-tab, other monitors and screenshots work."],
    ["Display", "WidescreenUI", "1", "1 = lay menus and HUD out for the monitor's aspect ratio instead of stretching 4:3."],
    ["Display", "UILayoutTrace", "0", "1 = log where each UI window is placed (for UI modding; T3UI.ini defines them)."],
  ].map(([section, key, value, description]) => ({ section, key, value, default: value, description })),
};

const now = Math.floor(Date.now() / 1000);
const maps = [
  ["Inn", "The Inn", 1412, true, 3, now - 3600, true, now - 3000, true],
  ["Docks", "The Docks", 2210, true, 12, now - 600, true, now - 5400, false],
  ["Museum", "The Museum", 1893, true, null, null, false, null, false],
  ["Cathedral", "The Cathedral", 2604, true, null, null, false, null, false],
  ["Keep", "The Keep", 1720, false, null, null, false, null, false],
  ["Manor", "The Manor", 1508, false, null, null, false, null, false],
  ["Lighthouse", "The Lighthouse", 980, false, null, null, false, null, false],
  ["Clocktower", "The Clocktower", 1311, false, null, null, false, null, false],
  ["Entry", "Main menu", 212, true, null, null, false, null, false],
].map(([id, title, actors, exported, edited, editsTime, patched, patchedTime, installed]) => ({
  id, title: exported ? title : null, size: (actors as number) * 9100, inGame: true, exported,
  actors: exported ? actors : null, editedActors: edited, editsTime, patched, patchedTime,
  stale: editsTime !== null && patchedTime !== null && (editsTime as number) > (patchedTime as number),
  installed, backedUp: installed,
}));

const game = () => ({
  dir: state.config.gameDir ?? "", ok: true, exeFound: true, sha1: "40bf68a54246bcde2fb5fcbc75b94dc7c7f78305",
  supported: true, steam: true, maps: maps.length, message: `Steam release, patch 1.1: supported. ${maps.length} maps.`,
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

let nextTask = 1;
function emit(name: string, payload: unknown) {
  handlers.get(name)?.forEach((h) => h(payload));
}

function fakeTask(title: string) {
  const id = nextTask++;
  const lines = [
    `+ python ${title.toLowerCase().replace(/ /g, "_")}.py`,
    "reading package tables...",
    "1412 actors -> Inn/Inn.actors.json (0.8 s)",
    "  96 mesh/skin pairs exported, 0 meshes not found in the bundles (6.1 s)",
    "  BSP: Inn_bsp.glb (7.9 s)",
    "  scene: Inn/Inn.tscn  (The Inn)",
  ];
  lines.forEach((line, i) => setTimeout(() => emit("task-output", { id, stream: "stdout", line }), 250 * (i + 1)));
  setTimeout(() => emit("task-exit", { id, code: 0, cancelled: false }), 250 * (lines.length + 1));
  return { id, title, command: `python tools/... (${title})` };
}

export async function mockCall<T>(cmd: string, args: Record<string, any> = {}): Promise<T> {
  await new Promise((r) => setTimeout(r, 60));
  const result: any = (() => {
    switch (cmd) {
      case "get_config": return { ...state.config };
      case "save_config": state.config = { ...args.config }; return { ...state.config };
      case "detect_all": return {
        games: [{ path: "D:\\SteamLibrary\\steamapps\\common\\Thief Deadly Shadows", source: "Steam library" }],
        godots: [{ path: "C:\\Tools\\Godot\\Godot_v4.7.2-stable_win64.exe", source: "user folder" }],
        pythons: [{ path: "C:\\Dev\\Thief3-Decomp\\.venv\\Scripts\\python.exe", source: "T3SDK .venv" },
                  { path: "C:\\Python312\\python.exe", source: "py launcher" }],
        sdkRoots: [{ path: "C:\\Dev\\Thief3-Decomp", source: "next to the launcher" }],
      };
      case "check_game": return { ...game(), dir: args.path };
      case "check_godot": return { path: args.path, ok: true, version: "4.7.2.stable.official", message: "Ready." };
      case "check_python": return { path: args.path, ok: true, version: "3.12.4", message: "Ready." };
      case "check_sdk_root": return { path: args.path, ok: true, mapTools: true, packTools: true, sdkBuilt: true, message: "Ready." };
      case "overview": return {
        game: state.config.gameDir ? game() : null,
        sdk: { installed: true, managed: true, built: true, buildable: true, settings: true },
        modsEnabled: state.mods.filter((m) => m.enabled).length,
        modsDisabled: state.mods.filter((m) => !m.enabled).length,
        maps: { total: maps.length, exported: maps.filter((m) => m.exported).length,
                edited: maps.filter((m) => m.editedActors).length, patched: maps.filter((m) => m.patched).length,
                installed: maps.filter((m) => m.installed).length },
        running: false,
      };
      case "list_maps": return maps.map((m) => ({ ...m }));
      case "list_mods": return state.mods.map((m) => ({ ...m }));
      case "set_mod_enabled": state.mods.find((m) => m.name === args.name)!.enabled = args.enabled; return null;
      case "read_sdk_settings": {
        const sections: any[] = [];
        for (const s of state.settings) {
          let sec = sections.find((x) => x.name === s.section);
          if (!sec) sections.push((sec = { name: s.section, settings: [] }));
          sec.settings.push({ key: s.key, value: s.value, default: s.default, description: s.description });
        }
        return { file: "...\\System\\T3SDK.ini", exists: true, template: "...\\sdk\\T3SDK.ini", sections };
      }
      case "write_sdk_settings":
        for (const c of args.changes) state.settings.find((s) => s.section === c.section && s.key === c.key)!.value = c.value;
        return null;
      case "create_sdk_settings": return null;
      case "read_sdk_log": return log.slice(-args.lines);
      case "launch_game": return "Asked Steam to start the game.";
      case "open_godot": case "open_location": case "open_link": case "cancel_task": return null;
      case "start_task": return fakeTask(taskTitle(args.spec));
      default: throw `mock: unknown command ${cmd}`;
    }
  })();
  return result as T;
}

function taskTitle(spec: any): string {
  const level = spec.level ?? "all maps";
  const titles: Record<string, string> = {
    sdkBuild: "Build T3SDK", sdkDeploy: "Install T3SDK", sdkUndeploy: "Remove T3SDK", export: `Export ${level}`,
    import: "Import into Godot", godotCheck: "Check the Godot project", roundtrip: `Round-trip check: ${level}`,
    repack: `Repack ${level}`, install: `Install ${level}`, restore: `Restore ${level}`,
  };
  return titles[spec.kind] ?? spec.kind;
}

export async function mockListen<T>(name: string, handler: (payload: T) => void) {
  if (!handlers.has(name)) handlers.set(name, new Set());
  handlers.get(name)!.add(handler as Handler);
  return () => handlers.get(name)!.delete(handler as Handler);
}

export async function mockPick(directory: boolean, title: string): Promise<string | null> {
  return window.prompt(`${title} (${directory ? "folder" : "file"} path)`);
}
