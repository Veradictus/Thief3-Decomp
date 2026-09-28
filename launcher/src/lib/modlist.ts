// The Mods page's logic that needs no Tauri: load-order moves, issue lookup,
// the index browser's filters and buttons, and messages. Plain functions of
// their arguments, so they are easy to test.
import type { IndexMod, IndexVersion, Issue, ModList, ModPackage, Severity, SyncReport } from "./api";

/** `order` with `id` moved to `index` (its place in the result). */
export function moveTo(order: string[], id: string, index: number): string[] {
  if (!order.includes(id)) return order;
  const rest = order.filter((o) => o !== id);
  const at = Math.max(0, Math.min(index, rest.length));
  return [...rest.slice(0, at), id, ...rest.slice(at)];
}

/** `order` with `id` moved up (negative) or down (positive) by `delta`. */
export function moveBy(order: string[], id: string, delta: number): string[] {
  const from = order.indexOf(id);
  return from < 0 ? order : moveTo(order, id, from + delta);
}

/** `order` with `id` just before `before`. */
export function moveBefore(order: string[], id: string, before: string): string[] {
  const rest = order.filter((o) => o !== id);
  const at = rest.indexOf(before);
  return at < 0 ? order : moveTo(order, id, at);
}

/**
 * Where a dragged row lands: its index in the new order, from the vertical
 * middles of every row (in order, the dragged one included) and the pointer.
 */
export function dropIndex(middles: number[], y: number, from: number): number {
  return middles.filter((mid, i) => i !== from && mid < y).length;
}

const rank: Record<Severity, number> = { error: 0, warning: 1, info: 2 };

/** The issues about one package (or, with null, the whole list), worst first. */
export function issuesFor(list: ModList | null, id: string | null): Issue[] {
  return (list?.issues ?? []).filter((i) => i.mod === id).sort((a, b) => rank[a.severity] - rank[b.severity]);
}

/** The worst severity among `issues`. */
export function worst(issues: { severity: Severity }[]): Severity | null {
  return issues.reduce<Severity | null>((w, i) => (w === null || rank[i.severity] < rank[w] ? i.severity : w), null);
}

export interface Badge {
  key: "code" | "content" | "textures";
  label: string;
  title: string;
}

/** What a package holds, as badges. */
export function badges(p: ModPackage): Badge[] {
  const list: Badge[] = [];
  const count = (n: number, one: string) => `${n.toString()} ${one}${n === 1 ? "" : "s"}`;
  if (p.code) list.push({ key: "code", label: "Code", title: `A T3SDK mod DLL (${p.entry ?? ""})` });
  if (p.files)
    list.push({ key: "content", label: "Content", title: `${count(p.files, "file")} placed in the game folder` });
  if (p.textures)
    list.push({
      key: "textures",
      label: "Textures",
      title: `${count(p.textures, "texture")} replaced in the game's bundles`,
    });
  return list;
}

/** The parts that are set, joined with " · ". */
export function meta(...parts: (string | number | null | undefined | false)[]): string {
  return parts.filter((p) => p !== null && p !== undefined && p !== false && p !== "").join(" · ");
}

/** "A", "A and B", "A, B and C". */
export function listText(names: string[]): string {
  if (names.length <= 1) return names[0] ?? "";
  return `${names.slice(0, -1).join(", ")} and ${names.at(-1) ?? ""}`;
}

/** What a change did, for a toast; null when there is nothing to say. */
export function reportText(report: SyncReport | null): string | null {
  if (!report) return null;
  const parts: string[] = [];
  const i = report.installed;
  if (i) {
    if (!i.previous) parts.push(`Installed ${i.name} ${i.version}.`);
    else if (i.previous === i.version) parts.push(`Reinstalled ${i.name} ${i.version}.`);
    else parts.push(`${i.name}: ${i.previous} → ${i.version}.`);
  }
  if (report.removed) parts.push(`Removed ${report.removed}.`);
  if (report.skipped.length) parts.push(`Not installed, skipped: ${report.skipped.join(", ")}.`);
  return parts.length ? parts.join(" ") : null;
}

/** The task that applies the texture packs of `mods`, or restores the originals. */
export function textureJobTitle(mods: string[]): string {
  return mods.length ? `Apply texture packs: ${mods.join(", ")}` : "Restore the original textures";
}

export const RESTORE_TITLE = "Restore the game's bundles, then place the mods' bundles";

const sameList = (a: string[], b: string[]) => a.length === b.length && a.every((x, i) => x === b[i]);

/**
 * What t3texpack.py has to do after a sync (docs/mods.md, "Content:
 * textures/"), given the texture packs of the `apply` jobs already on their
 * way: `restore` when game bundles wait to be placed or removed (the packs
 * then go on again), `apply` when the enabled packs changed, or with `again`.
 * Null when there is nothing to add.
 */
export function textureSteps(
  t: { needed: boolean; mods: string[]; bundles: string[] },
  pendingApplies: string[][],
  again = false,
): { restore: boolean; apply: string[] | null } | null {
  const restore = t.bundles.length > 0;
  const apply = restore ? t.mods.length > 0 : t.needed || again;
  if (!restore && !apply) return null;
  if (!restore && !again && pendingApplies.some((m) => sameList(m, t.mods))) return null;
  return { restore, apply: apply ? t.mods : null };
}

// ---- the index browser ------------------------------------------------------------

/** A mod matches when every word is in its name, id, authors, description or tags, and it has `tag`. */
export function matches(mod: IndexMod, query: string, tag: string | null): boolean {
  if (tag && !mod.tags.includes(tag)) return false;
  const text = [mod.name, mod.id, mod.description ?? "", ...mod.authors, ...mod.tags].join(" ").toLowerCase();
  return query
    .toLowerCase()
    .split(/\s+/)
    .filter(Boolean)
    .every((word) => text.includes(word));
}

/** Tags used in the index, most used first. */
export function indexTags(mods: IndexMod[]): string[] {
  const counts = new Map<string, number>();
  for (const tag of mods.flatMap((m) => m.tags)) counts.set(tag, (counts.get(tag) ?? 0) + 1);
  return [...counts.entries()].sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0])).map(([tag]) => tag);
}

/** Compares two semantic versions (numbers, then pre-releases before releases). */
export function compareVersions(a: string, b: string): number {
  const split = (v: string) => {
    const [core = "", pre = ""] = v.split("+")[0]?.split(/-(.*)/s) ?? [];
    return { nums: core.split(".").map(Number), pre };
  };
  const x = split(a);
  const y = split(b);
  for (let i = 0; i < 3; i++) {
    const d = (x.nums[i] ?? 0) - (y.nums[i] ?? 0);
    if (d) return Math.sign(d);
  }
  if (x.pre === y.pre) return 0;
  if (!x.pre) return 1;
  if (!y.pre) return -1;
  const xs = x.pre.split(".");
  const ys = y.pre.split(".");
  for (let i = 0; i < Math.max(xs.length, ys.length); i++) {
    const p = xs[i];
    const q = ys[i];
    if (p === undefined) return -1;
    if (q === undefined) return 1;
    const pn = /^\d+$/.test(p);
    const qn = /^\d+$/.test(q);
    if (pn && qn && Number(p) !== Number(q)) return Math.sign(Number(p) - Number(q));
    if (pn !== qn) return pn ? -1 : 1;
    if (p !== q) return p < q ? -1 : 1;
  }
  return 0;
}

export interface InstallButton {
  label: string;
  /** The version the button installs; null when there is nothing to do. */
  version: string | null;
  primary: boolean;
}

/** The button for `version` of an index mod, given what is installed. */
export function installButton(mod: IndexMod, version: IndexVersion | undefined): InstallButton {
  if (!version) return { label: "Not available", version: null, primary: false };
  const v = version.version;
  if (!mod.installed) return { label: `Install ${v}`, version: v, primary: version.compatible };
  const order = compareVersions(v, mod.installed);
  if (order === 0) return { label: "Installed", version: null, primary: false };
  if (order > 0) return { label: `Update to ${v}`, version: v, primary: version.compatible };
  return { label: `Install ${v} (older)`, version: v, primary: false };
}
