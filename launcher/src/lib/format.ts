// Display helpers: plain functions of their arguments, so they are easy to test.
import type { Setting } from "./api";

const dateFormat = new Intl.DateTimeFormat(undefined, { dateStyle: "medium" });
const dateTimeFormat = new Intl.DateTimeFormat(undefined, { dateStyle: "medium", timeStyle: "short" });

/** "just now", "5 min ago", "3 h ago", else the date. `seconds` is a Unix time. */
export function ago(seconds: number | null, now = Date.now()): string {
  if (!seconds) return "";
  const d = now / 1000 - seconds;
  if (d < 60) return "just now";
  if (d < 3600) return `${Math.floor(d / 60).toString()} min ago`;
  if (d < 86400) return `${Math.floor(d / 3600).toString()} h ago`;
  return dateFormat.format(seconds * 1000);
}

export function bytes(n: number | null): string {
  if (n === null) return "";
  if (n < 1024 * 1024) return `${(n / 1024).toFixed(0)} KB`;
  return `${(n / 1024 / 1024).toFixed(1)} MB`;
}

/** Time between two millisecond timestamps: "4.2 s", "2 min 5 s". */
export function elapsed(started: number | null, ended: number | null, now = Date.now()): string {
  if (!started) return "";
  const s = ((ended ?? now) - started) / 1000;
  return s < 60 ? `${s.toFixed(1)} s` : `${Math.floor(s / 60).toString()} min ${Math.round(s % 60).toString()} s`;
}

/** An INI key as a label: "SkipIntros" -> "Skip intros", "UILayoutTrace" -> "UI layout trace". */
export function settingLabel(key: string): string {
  return key
    .replace(/([a-z0-9])([A-Z])/g, "$1 $2")
    .replace(/([A-Z]+)([A-Z][a-z])/g, "$1 $2")
    .replace(/ ([A-Z][a-z])/g, (m) => m.toLowerCase());
}

/** T3SDK.ini comments read "1 = do this."; next to a switch, "Do this." says it. */
export function settingDescription(setting: Setting): string {
  return setting.description.replace(/^1 = /, "").replace(/^./, (c) => c.toUpperCase());
}

/**
 * On/off switches: a default (or value) of 0 or 1, and a comment that says what
 * 1 does. A number that merely defaults to 0 ("MaxFPS: 0 = no limit") is not one.
 */
export const isSwitch = (setting: Setting) =>
  ["0", "1"].includes(setting.default ?? setting.value) &&
  (!setting.description || setting.description.startsWith("1 = "));

/** Settings named ...Key hold a virtual-key code. */
export const isKeySetting = (setting: Setting) => /key$/i.test(setting.key);

const KEY_NAMES: Record<string, string> = {
  "0": "Off",
  ...Object.fromEntries(
    Array.from({ length: 12 }, (_, i) => [`0x${(0x70 + i).toString(16)}`, `F${(i + 1).toString()}`]),
  ),
};

/** The name of a virtual-key code as T3SDK.ini writes it ("0x79" -> "F10"), or "". */
export function keyName(code: string): string {
  return KEY_NAMES[code.trim().toLowerCase()] ?? "";
}

/** A Unix time as date and time in the user's locale, or "". */
export function dateTime(seconds: number | null): string {
  return seconds ? dateTimeFormat.format(seconds * 1000) : "";
}

/** How much of a download is done, 0-100, or null while its size is unknown. */
export function percent(done: number, total: number | null): number | null {
  if (!total || total <= 0) return null;
  return Math.max(0, Math.min(100, Math.floor((done / total) * 100)));
}

/** The first https link in a text (release notes), without trailing punctuation. */
export function firstLink(text: string | null): string | null {
  const match = text ? /https:\/\/[^\s<>()"'\]]+/.exec(text) : null;
  return match ? match[0].replace(/[.,;:!?]+$/, "") : null;
}
