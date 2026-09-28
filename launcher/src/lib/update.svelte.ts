// Launcher updates: the start-up check (at most daily, see update.rs), the
// banner's state, and the download with its progress. Builds without the
// update key report `enabled: false` and never check.
import { api, errorText, onEvent, type UpdateInfo, type UpdateProgress, type UpdaterStatus } from "./api";
import { guard, toast } from "./app.svelte";

/** Where portable and unsigned builds get new versions. */
export const RELEASES_URL = "https://github.com/Veradictus/Thief3-Decomp/releases/latest";

interface UpdaterState {
  status: UpdaterStatus | null;
  /** The newer version found by the last check. */
  update: UpdateInfo | null;
  checking: boolean;
  /** A check ran in this session, so "up to date" can be said. */
  checked: boolean;
  error: string;
  installing: boolean;
  progress: UpdateProgress | null;
  /** The banner was closed ("Later"). */
  dismissed: boolean;
}

export const updater = $state<UpdaterState>({
  status: null,
  update: null,
  checking: false,
  checked: false,
  error: "",
  installing: false,
  progress: null,
  dismissed: false,
});

export async function loadUpdaterStatus() {
  updater.status = (await guard(api.updaterStatus())) ?? updater.status;
}

/** `auto` is the start-up check: quiet about errors (being offline is normal). */
export async function checkForUpdate(auto: boolean) {
  if (updater.checking || updater.installing) return;
  updater.checking = true;
  updater.error = "";
  try {
    const result = await api.checkUpdate(auto);
    if (result.checked) {
      updater.update = result.update;
      updater.checked = true;
      updater.dismissed = false;
      await loadUpdaterStatus();
    }
  } catch (e) {
    updater.error = errorText(e);
    if (!auto) toast(updater.error, "error");
  } finally {
    updater.checking = false;
  }
}

export async function startupUpdateCheck() {
  await loadUpdaterStatus();
  if (updater.status?.enabled) await checkForUpdate(true);
}

let listening = false;

/** Downloads and installs the update. On Windows the installer then takes
 * over and restarts the launcher, so this only returns on failure (or in the
 * browser preview). */
export async function installUpdate() {
  if (updater.installing) return;
  if (updater.status?.portable) {
    void guard(api.openLink(RELEASES_URL));
    return;
  }
  updater.installing = true;
  updater.progress = { downloaded: 0, total: null, finished: false };
  try {
    if (!listening) {
      listening = true;
      await onEvent<UpdateProgress>("update-progress", (p) => {
        updater.progress = p;
      });
    }
    await api.installUpdate();
    updater.update = null;
    toast("Update installed. Restart the launcher to use it.");
  } catch (e) {
    toast(errorText(e), "error");
  } finally {
    updater.installing = false;
    updater.progress = null;
  }
}
