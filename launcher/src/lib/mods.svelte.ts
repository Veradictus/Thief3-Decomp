// The Mods page's state: the installed list, the mod index, and the changes.
// Every change is saved and applied by the backend at once (it returns the new
// list); when the enabled texture packs changed, the t3texpack.py job is queued
// here, replacing a queued one that has not started yet.
import {
  api,
  errorText,
  onEvent,
  onFileDrop,
  type DownloadProgress,
  type FixAction,
  type ModIndex,
  type ModList,
  type ProfileAction,
} from "./api";
import { app, cancel, enqueue, guard, jobs, refresh, toast, type Job } from "./app.svelte";
import { RESTORE_TITLE, moveBefore, reportText, textureJobTitle, textureSteps } from "./modlist";

interface ModsState {
  list: ModList | null;
  index: ModIndex | null;
  indexError: string;
  indexLoading: boolean;
  /** A change is being applied. */
  busy: boolean;
  /** .t3mod files are being dragged over the window. */
  dragging: boolean;
  download: DownloadProgress | null;
  /** Problems the last change ran into (files it could not place, ...). */
  notice: { title: string; lines: string[] } | null;
}

export const mods = $state<ModsState>({
  list: null,
  index: null,
  indexError: "",
  indexLoading: false,
  busy: false,
  dragging: false,
  download: null,
  notice: null,
});

export async function loadMods() {
  mods.list = (await guard(api.listMods())) ?? mods.list;
}

/** Texture jobs that have not finished. */
export function textureJobs(): Job[] {
  return jobs.list.filter(
    (j) =>
      (j.spec.kind === "texturePacks" || j.spec.kind === "textureRestore") &&
      (j.state === "queued" || j.state === "running"),
  );
}

/**
 * Queues what t3texpack.py has to do after a sync (docs/mods.md, "Content:
 * textures/"): `restore` first when game bundles wait to be placed or removed
 * (its success places them), then `apply` with the enabled packs. Queued
 * texture jobs that have not started are replaced; an `apply` of the same
 * packs already on its way is kept. `again` applies even when nothing changed.
 */
export function queueTextures(t: ModList["textures"], again = false) {
  const pending = textureJobs();
  const applies = pending.flatMap((j) => (j.spec.kind === "texturePacks" ? [j.spec.mods] : []));
  const steps = textureSteps(t, applies, again);
  if (!steps) return;
  for (const j of pending) if (j.state === "queued") cancel(j);
  const first = steps.restore ? enqueue({ kind: "textureRestore" }, RESTORE_TITLE) : null;
  if (steps.apply) enqueue({ kind: "texturePacks", mods: steps.apply }, textureJobTitle(steps.apply), first);
}

async function apply(work: Promise<ModList>): Promise<ModList | undefined> {
  mods.busy = true;
  try {
    const list = await work;
    mods.list = list;
    const r = list.report;
    const text = reportText(r);
    if (text) toast(text);
    const lines = [
      ...(r?.errors ?? []),
      ...(r?.changed ?? []).map((c) => `Changed outside the launcher, left as it is: ${c}`),
    ];
    mods.notice = lines.length ? { title: "Some files were not updated", lines } : null;
    queueTextures(list.textures);
    if (mods.index) void loadIndex(false);
    void refresh();
    return list;
  } catch (e) {
    toast(errorText(e), "error");
    // Switches flipped in the page go back to what is really there.
    void loadMods();
    return undefined;
  } finally {
    mods.busy = false;
  }
}

export const setPackageEnabled = (id: string, enabled: boolean) => apply(api.setPackageEnabled(id, enabled));
export const setLooseEnabled = (name: string, enabled: boolean) => apply(api.setModEnabled(name, enabled));
export const setOrder = (order: string[]) => apply(api.setModOrder(order));
export const removeMod = (id: string) => apply(api.removeMod(id));
export const syncMods = () => apply(api.syncMods());
export const profile = (action: ProfileAction) => apply(api.modProfile(action));

export function fix(action: FixAction) {
  switch (action.kind) {
    case "enable":
      return setPackageEnabled(action.id, true);
    case "disable":
      return setPackageEnabled(action.id, false);
    case "moveBefore": {
      const order = mods.list?.packages.map((p) => p.id) ?? [];
      return setOrder(moveBefore(order, action.id, action.before));
    }
  }
}

/** Installs .t3mod files one after the other; other files are ignored. */
export async function installFiles(paths: string[]) {
  const packages = paths.filter((p) => p.toLowerCase().endsWith(".t3mod"));
  if (!packages.length) {
    if (paths.length) toast("Only .t3mod mod packages can be installed here.", "error");
    return;
  }
  for (const path of packages) await apply(api.installMod(path));
}

export async function loadIndex(refreshIndex: boolean) {
  mods.indexLoading = true;
  try {
    mods.index = await api.modIndex(refreshIndex);
    mods.indexError = "";
  } catch (e) {
    mods.indexError = errorText(e);
  } finally {
    mods.indexLoading = false;
  }
}

export async function installFromIndex(id: string, version: string) {
  mods.download = { id, received: 0, total: 0 };
  try {
    await apply(api.installFromIndex(id, version));
  } finally {
    mods.download = null;
  }
}

let listening = false;

/** Download progress, and .t3mod files dropped onto the window (from any page). */
export async function listenForMods() {
  if (listening) return;
  listening = true;
  await onEvent<DownloadProgress>("mod-download", (p) => {
    if (mods.download?.id === p.id) mods.download = p;
  });
  await onFileDrop((e) => {
    if (e.type === "enter") mods.dragging = e.paths.some((p) => p.toLowerCase().endsWith(".t3mod"));
    else if (e.type === "leave") mods.dragging = false;
    else if (e.type === "drop") {
      mods.dragging = false;
      if (!e.paths.some((p) => p.toLowerCase().endsWith(".t3mod"))) return;
      app.page = "mods";
      void installFiles(e.paths);
    }
  });
}
