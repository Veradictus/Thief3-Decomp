// The Mods page's part of the browser mock (mock.ts): installed packages, loose
// DLLs, profiles and a mod index, all made up. The checks are a small copy of
// the backend's (src-tauri/src/mods/checks.rs), enough to show every kind of
// issue in the preview.
import type {
  IndexMod,
  IndexNote,
  IndexVersion,
  Issue,
  LooseMod,
  ModIndex,
  ModList,
  ModPackage,
  ProfileAction,
  SyncReport,
} from "./api";
import { compareVersions } from "./modlist";

type Args = Record<string, unknown>;
type Emit = (name: string, payload: unknown) => void;

const DAY = 86400;
const now = Math.floor(Date.now() / 1000);

function pkg(p: Partial<ModPackage> & Pick<ModPackage, "id" | "name" | "version">): ModPackage {
  return {
    authors: ["T3SDK contributors"],
    description: null,
    homepage: null,
    license: "MIT",
    tags: [],
    entry: null,
    api: null,
    requires: {},
    conflicts: [],
    enabled: true,
    active: true,
    position: 0,
    size: 20480,
    code: false,
    files: 0,
    textures: 0,
    error: null,
    ...p,
  };
}

const code = (id: string) => ({ entry: `${id}.dll`, api: 1, code: true });

type IndexRow = Omit<IndexMod, "installed" | "enabled" | "versions" | "recommended"> & {
  versions: Omit<IndexVersion, "compatible" | "notes" | "url">[];
};

const indexRows: IndexRow[] = [
  {
    id: "better-lockpicks",
    name: "Better Lockpicks",
    description: "Lockpicking without the fuss: one continuous turn instead of the pin game.",
    authors: ["Someone"],
    homepage: "https://example.org/better-lockpicks",
    license: "MIT",
    tags: ["gameplay"],
    versions: [
      {
        version: "1.3.0",
        size: 51200,
        released: "2026-09-20",
        api: 1,
        requires: { "sdk-ui-helpers": ">=0.3.0" },
        conflicts: [],
      },
      {
        version: "1.2.0",
        size: 48213,
        released: "2026-09-01",
        api: 1,
        requires: { "sdk-ui-helpers": ">=0.3.0" },
        conflicts: [],
      },
    ],
  },
  {
    id: "sdk-ui-helpers",
    name: "SDK UI Helpers",
    description: "Shared code for mods that draw their own menus and HUD elements.",
    authors: ["T3SDK contributors"],
    homepage: null,
    license: "MIT",
    tags: ["library", "ui"],
    versions: [{ version: "0.3.2", size: 30720, released: "2026-08-14", api: 1, requires: {}, conflicts: [] }],
  },
  {
    id: "coop-prototype",
    name: "Co-op Prototype",
    description: "Two thieves, one city. An early test of player sync over UDP; expect desyncs.",
    authors: ["Netcode Guild"],
    homepage: "https://example.org/coop",
    license: "GPL-3.0",
    tags: ["gameplay", "tools"],
    versions: [
      {
        version: "0.2.0",
        size: 402000,
        released: "2026-09-25",
        api: 2,
        requires: { "sdk-net": ">=0.1.0" },
        conflicts: [],
      },
      {
        version: "0.1.0",
        size: 388000,
        released: "2026-08-30",
        api: 1,
        requires: { "sdk-net": ">=0.1.0" },
        conflicts: [],
      },
    ],
  },
  {
    id: "sdk-net",
    name: "SDK Net",
    description: "A UDP transport (ENet) for mods, with the game's frame loop driving it.",
    authors: ["Netcode Guild"],
    homepage: null,
    license: "MIT",
    tags: ["library"],
    versions: [{ version: "0.1.4", size: 120000, released: "2026-09-10", api: 1, requires: {}, conflicts: [] }],
  },
  {
    id: "clean-fonts",
    name: "Clean Fonts",
    description: "Sharper menu and journal fonts at high resolutions.",
    authors: ["Typesetter"],
    homepage: null,
    license: "CC-BY-4.0",
    tags: ["ui", "graphics"],
    versions: [
      { version: "2.0.1", size: 880000, released: "2026-07-02", api: null, requires: {}, conflicts: ["hd-ui"] },
    ],
  },
  ...(
    [
      [
        "fov-control",
        "FOV Control",
        "Hor+ field of view for wide screens.",
        "Lens",
        ["graphics", "fixes"],
        "1.5.0",
        true,
      ],
      ["stealth-meter", "Stealth Meter", "The light gem as a number, too.", "Shade", ["ui"], "2.0.0", true],
      ["loot-tally", "Loot Tally", "Shows the loot total on the map screen.", "Fence", ["ui"], "1.1.0", true],
      ["quicksave-slots", "Quicksave Slots", "Ten rotating quicksave slots.", "Keeper", ["gameplay"], "0.9.2", true],
      [
        "subtitles-plus",
        "Subtitles Plus",
        "Subtitles for every conversation.",
        "Scribe",
        ["ui", "audio"],
        "1.2.0",
        true,
      ],
      ["city-ambience", "City Ambience", "Restored night sounds in the City.", "Ambience", ["audio"], "1.0.3", false],
      ["hd-water", "HD Water", "Sharper water and ripples in every level.", "Glyph", ["textures"], "0.4.0", false],
      ["keeper-lore", "Keeper Lore", "Twenty new Keeper glyph books to find.", "Scribe", ["maps"], "1.0.0", false],
    ] satisfies [string, string, string, string, string[], string, boolean][]
  ).map(([id, name, description, author, tags, version, code]) => ({
    id,
    name,
    description,
    authors: [author],
    homepage: null,
    license: "MIT",
    tags,
    versions: [{ version, size: 64000, released: "2026-09-12", api: code ? 1 : null, requires: {}, conflicts: [] }],
  })),
  {
    id: "quiet-city",
    name: "Quiet City",
    description: "Fewer barks from city watch patrols. Replaces the voice set list only.",
    authors: ["Ambience"],
    homepage: null,
    license: "MIT",
    tags: ["audio"],
    versions: [{ version: "1.0.0", size: 9000, released: "2026-06-11", api: null, requires: {}, conflicts: [] }],
  },
];

export function mockMods(emit: Emit) {
  let packages: ModPackage[] = [
    pkg({
      id: "sdk-ui-helpers",
      name: "SDK UI Helpers",
      version: "0.3.2",
      description: "Shared code for mods that draw their own menus and HUD elements.",
      tags: ["library", "ui"],
      ...code("sdk-ui-helpers"),
    }),
    pkg({
      id: "better-lockpicks",
      name: "Better Lockpicks",
      version: "1.2.0",
      authors: ["Someone"],
      description: "Lockpicking without the fuss.",
      homepage: "https://example.org/better-lockpicks",
      tags: ["gameplay"],
      requires: { "sdk-ui-helpers": ">=0.3.0" },
      ...code("better-lockpicks"),
      size: 48213,
    }),
    pkg({
      id: "hd-ui",
      name: "HD Interface",
      version: "3.1.0",
      authors: ["Glyph", "Ink"],
      description: "Loading screens, journal pages and the compass redrawn at 4x.",
      tags: ["ui", "graphics"],
      files: 42,
      size: 58_000_000,
    }),
    pkg({
      id: "hd-textures",
      name: "HD Textures",
      version: "0.1.0-beta.2",
      authors: ["A", "B"],
      description: "Upscaled stone, wood and metal for the City.",
      tags: ["textures", "graphics"],
      textures: 812,
      size: 910_000_000,
      enabled: false,
    }),
    pkg({
      id: "coop-prototype",
      name: "Co-op Prototype",
      version: "0.1.0",
      authors: ["Netcode Guild"],
      description: "Two thieves, one city.",
      tags: ["gameplay"],
      requires: { "sdk-net": ">=0.1.0" },
      ...code("coop-prototype"),
      enabled: false,
    }),
    ...(
      [
        ["fov-control", "FOV Control", "1.4.1", ["Lens"], "Hor+ field of view for wide screens.", true, 0],
        ["stealth-meter", "Stealth Meter", "2.0.0", ["Shade"], "The light gem as a number, too.", true, 0],
        ["loot-tally", "Loot Tally", "1.1.0", ["Fence"], "Shows the loot total on the map screen.", true, 0],
        ["quicksave-slots", "Quicksave Slots", "0.9.2", ["Keeper"], "Ten rotating quicksave slots.", true, 0],
        ["clean-fonts", "Clean Fonts", "2.0.1", ["Typesetter"], "Sharper menu and journal fonts.", true, 3],
        ["city-ambience", "City Ambience", "1.0.3", ["Ambience"], "Restored night sounds in the City.", false, 64],
        ["subtitles-plus", "Subtitles Plus", "1.2.0", ["Scribe"], "Subtitles for every conversation.", true, 0],
      ] satisfies [string, string, string, string[], string, boolean, number][]
    ).map(([id, name, version, authors, description, enabled, files]) =>
      pkg({ id, name, version, authors, description, enabled, ...(files ? { files } : code(id)) }),
    ),
  ];
  const loose: LooseMod[] = [
    { name: "ai_senses_log", enabled: false, size: 41984, modified: now - 12 * DAY },
    { name: "debug_camera", enabled: true, size: 30720, modified: now - 20 * DAY },
    { name: "hello", enabled: true, size: 14336, modified: now - 3 * DAY },
    { name: "old_experiment", enabled: false, size: 188416, modified: now - 40 * DAY },
  ];
  let profile = "Default";
  const profiles = new Map<string, { order: string[]; enabled: string[] }>([["Vanilla", { order: [], enabled: [] }]]);
  let texturesApplied: string[] = [];

  const byId = (id: string) => packages.find((p) => p.id === id);
  const current = () => ({
    order: packages.map((p) => p.id),
    enabled: packages.filter((p) => p.enabled).map((p) => p.id),
  });

  function check(): Issue[] {
    const issues: Issue[] = [];
    packages.forEach((p, i) => {
      p.position = i;
      p.active = p.enabled && !p.error;
    });
    const on = packages.filter((p) => p.enabled);
    for (const a of on)
      for (const b of on)
        if (a.id < b.id && (a.conflicts.includes(b.id) || b.conflicts.includes(a.id)))
          for (const [x, y] of [
            [a, b],
            [b, a],
          ] as const) {
            x.active = false;
            issues.push({
              severity: "error",
              mod: x.id,
              message: `Conflicts with ${y.id}; both stay off until one is disabled`,
              fix: { label: `Disable ${y.id}`, action: { kind: "disable", id: y.id } },
            });
          }
    for (let changed = true; changed;) {
      changed = false;
      for (const p of packages)
        if (p.active && Object.keys(p.requires).some((need) => !byId(need)?.active)) {
          p.active = false;
          changed = true;
        }
    }
    for (const p of on)
      for (const [need, range] of Object.entries(p.requires)) {
        const q = byId(need);
        if (!q)
          issues.push({
            severity: "error",
            mod: p.id,
            message: `Needs ${need} ${range}, which is not installed`,
            fix: null,
          });
        else if (!q.enabled)
          issues.push({
            severity: "error",
            mod: p.id,
            message: `Needs ${need}, which is disabled`,
            fix: { label: `Enable ${need}`, action: { kind: "enable", id: need } },
          });
        else if (q.position > p.position)
          issues.push({
            severity: "warning",
            mod: p.id,
            message: `${need} should load before ${p.id}: it is a requirement`,
            fix: { label: `Move ${need} before ${p.id}`, action: { kind: "moveBefore", id: need, before: p.id } },
          });
      }
    const fonts = byId("clean-fonts");
    const ui = byId("hd-ui");
    if (fonts?.active && ui?.active) {
      const later = fonts.position > ui.position ? fonts : ui;
      const earlier = later === fonts ? ui : fonts;
      issues.push({
        severity: "info",
        mod: later.id,
        message: `Replaces 3 files of ${earlier.id} (such as Content/T3/Bitmaps/Fonts/Journal.dds): it loads later, so it wins`,
        fix: null,
      });
    }
    return issues;
  }

  function list(report: SyncReport | null = null): ModList {
    const issues = check();
    const tex = packages.filter((p) => p.active && p.textures).map((p) => p.id);
    return {
      dir: "D:\\SteamLibrary\\steamapps\\common\\Thief Deadly Shadows\\System\\mods",
      packages: packages.map((p) => ({ ...p })),
      loose: loose.map((m) => ({ ...m })),
      profile,
      profiles: [...new Set([profile, ...profiles.keys()])].sort((a, b) => a.localeCompare(b)),
      issues,
      sdk: { installed: true, api: 1 },
      textures: { needed: tex.join() !== texturesApplied.join(), mods: tex, bundles: [] },
      report,
    };
  }

  const blank = (): SyncReport => ({
    placed: 0,
    restored: 0,
    changed: [],
    errors: [],
    skipped: [],
    installed: null,
    removed: null,
  });

  function changed(report: SyncReport = blank()) {
    profiles.set(profile, current());
    return list(report);
  }

  function add(p: ModPackage, report: SyncReport) {
    const old = byId(p.id);
    report.installed = { id: p.id, name: p.name, version: p.version ?? "", previous: old?.version ?? null };
    if (old) Object.assign(old, { ...p, enabled: old.enabled });
    else packages.push(p);
    return changed(report);
  }

  function profileAction(action: ProfileAction): ModList {
    const report = blank();
    const find = (name: string) => [...profiles.keys()].find((k) => k.toLowerCase() === name.toLowerCase());
    switch (action.kind) {
      case "saveAs":
        if (find(action.name)) throw new Error(`there is already a profile named ${action.name}`);
        profile = action.name.trim();
        break;
      case "switch": {
        const name = find(action.name);
        const saved = name ? profiles.get(name) : undefined;
        if (!name || !saved) throw new Error(`no profile named ${action.name}`);
        profile = name;
        report.skipped = saved.order.filter((id) => !byId(id));
        const rank = (id: string) => (saved.order.includes(id) ? saved.order.indexOf(id) : 1000);
        packages = packages.sort((a, b) => rank(a.id) - rank(b.id));
        for (const p of packages) p.enabled = saved.enabled.includes(p.id);
        break;
      }
      case "delete": {
        const name = find(action.name);
        if (!name) throw new Error(`no profile named ${action.name}`);
        if (name === profile) throw new Error("switch to another profile before deleting this one");
        profiles.delete(name);
        return list(report);
      }
      case "rename": {
        const name = find(action.from);
        const saved = name ? profiles.get(name) : undefined;
        if (!name || !saved) throw new Error(`no profile named ${action.from}`);
        profiles.delete(name);
        profiles.set(action.to.trim(), saved);
        if (profile === name) profile = action.to.trim();
        return list(report);
      }
    }
    return changed(report);
  }

  function indexView(): ModIndex {
    const enabled = (id: string) => byId(id)?.enabled ?? false;
    const mods: IndexMod[] = indexRows.map((row) => {
      const installed = byId(row.id)?.version ?? null;
      const versions: IndexVersion[] = row.versions.map((v) => {
        const notes: IndexNote[] = [];
        if (v.api !== null && v.api > 1)
          notes.push({
            severity: "error",
            message: `Needs a newer T3SDK (API version ${v.api.toString()}; the installed SDK has 1)`,
          });
        for (const [need, range] of Object.entries(v.requires)) {
          if (!byId(need))
            notes.push(
              indexRows.some((r) => r.id === need)
                ? { severity: "warning", message: `Needs ${need} ${range}: install it too (it is in the index)` }
                : { severity: "error", message: `Needs ${need} ${range}, which is not installed or in the index` },
            );
          else if (!enabled(need))
            notes.push({ severity: "warning", message: `Needs ${need}, which is installed but disabled` });
        }
        for (const c of v.conflicts)
          if (enabled(c)) notes.push({ severity: "error", message: `Conflicts with ${c}, which is enabled` });
        const url = `https://example.org/${row.id}-${v.version}.t3mod`;
        return { ...v, url, notes, compatible: !notes.some((n) => n.severity === "error") };
      });
      const recommended =
        versions.find((v) => v.compatible && !v.version.includes("-")) ??
        versions.find((v) => v.compatible) ??
        versions[0];
      return { ...row, installed, enabled: enabled(row.id), versions, recommended: recommended?.version ?? null };
    });
    const updates = mods.flatMap((m) => {
      const newer = m.installed
        ? m.versions.find((v) => v.compatible && compareVersions(v.version, m.installed ?? "") > 0)
        : undefined;
      return newer && m.installed ? [{ id: m.id, name: m.name, installed: m.installed, latest: newer.version }] : [];
    });
    return {
      url: "https://veradictus.github.io/Thief3-Decomp/modindex/index.json",
      generated: new Date((now - DAY) * 1000).toISOString(),
      skipped: 0,
      mods,
      updates,
    };
  }

  async function download(id: string, version: string): Promise<ModList> {
    const row = indexRows.find((r) => r.id === id);
    const v = row?.versions.find((x) => x.version === version);
    if (!row || !v) throw new Error(`${id} ${version} is not in the mod index`);
    for (let step = 1; step <= 10; step++) {
      await new Promise((resolve) => setTimeout(resolve, 120));
      emit("mod-download", { id, received: Math.round((v.size * step) / 10), total: v.size });
    }
    const p = pkg({
      id,
      name: row.name,
      version,
      authors: row.authors,
      description: row.description,
      homepage: row.homepage,
      license: row.license,
      tags: row.tags,
      requires: v.requires,
      conflicts: v.conflicts,
      size: v.size,
      ...(v.api !== null ? code(id) : { files: 12 }),
    });
    return add(p, blank());
  }

  const text = (args: Args, key: string) => {
    const value = args[key];
    if (typeof value !== "string") throw new Error(`mock: ${key} must be a string`);
    return value;
  };

  const commands: Record<string, (args: Args) => unknown> = {
    list_mods: () => list(),
    set_mod_enabled: (args) => {
      const m = loose.find((l) => l.name === text(args, "name"));
      if (!m) throw new Error("mock: no such mod");
      m.enabled = args.enabled === true;
      return list();
    },
    set_package_enabled: (args) => {
      const p = byId(text(args, "id"));
      if (!p) throw new Error(`${text(args, "id")} is not installed`);
      p.enabled = args.enabled === true;
      return changed();
    },
    set_mod_order: (args) => {
      const order = args.order as string[];
      packages = order.map((id) => byId(id)).filter((p): p is ModPackage => p !== undefined);
      return changed();
    },
    install_mod: (args) => {
      const path = text(args, "path");
      const file = path.split(/[\\/]/).pop() ?? path;
      const found = /^([a-z0-9][a-z0-9_-]*?)-(\d+\.\d+\.\d+(?:-[0-9A-Za-z.-]+)?)\.t3mod$/i.exec(file);
      if (!found)
        throw new Error(`${file} was refused: mod.json: id: not a mod id (the preview reads <id>-<version>.t3mod)`);
      const [, id = "", version = ""] = found;
      const name = id.replace(/[-_]/g, " ").replace(/\b\w/g, (c) => c.toUpperCase());
      return add(pkg({ id: id.toLowerCase(), name, version, files: 7, size: 1_200_000 }), blank());
    },
    remove_mod: (args) => {
      const id = text(args, "id");
      if (!byId(id)) throw new Error(`${id} is not installed`);
      packages = packages.filter((p) => p.id !== id);
      for (const saved of profiles.values()) {
        saved.order = saved.order.filter((o) => o !== id);
        saved.enabled = saved.enabled.filter((o) => o !== id);
      }
      return changed({ ...blank(), removed: id });
    },
    sync_mods: () => changed(),
    mod_profile: (args) => profileAction(args.action as ProfileAction),
    mod_index: () => indexView(),
    install_from_index: (args) => download(text(args, "id"), text(args, "version")),
  };

  return {
    commands,
    /** Enabled and switched-off mods, for the overview. */
    counts: () => {
      const on = packages.filter((p) => p.enabled).length + loose.filter((m) => m.enabled).length;
      return { on, off: packages.length + loose.length - on };
    },
    /** A texture job finished. */
    texturesApplied: (packs: string[]) => {
      texturesApplied = [...packs];
    },
  };
}
