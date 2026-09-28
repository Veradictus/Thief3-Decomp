import { describe, expect, it } from "vitest";
import type { Setting } from "./api";
import { ago, bytes, elapsed, isKeySetting, isSwitch, keyName, settingDescription, settingLabel } from "./format";

const setting = (key: string, value: string, description = "", defaultValue: string | null = value): Setting => ({
  key,
  value,
  default: defaultValue,
  description,
});

describe("ago", () => {
  const now = Date.UTC(2026, 8, 28, 12, 0, 0);
  const at = (secondsBefore: number) => now / 1000 - secondsBefore;

  it("is empty without a time", () => {
    expect(ago(null, now)).toBe("");
  });
  it("counts minutes and hours", () => {
    expect(ago(at(30), now)).toBe("just now");
    expect(ago(at(5 * 60), now)).toBe("5 min ago");
    expect(ago(at(3 * 3600 + 10), now)).toBe("3 h ago");
  });
  it("falls back to the date after a day", () => {
    expect(ago(at(3 * 86400), now)).not.toMatch(/ago|now/);
  });
});

describe("bytes", () => {
  it("uses KB below a megabyte and MB above", () => {
    expect(bytes(null)).toBe("");
    expect(bytes(14336)).toBe("14 KB");
    expect(bytes(12.5 * 1024 * 1024)).toBe("12.5 MB");
  });
});

describe("elapsed", () => {
  it("is empty before a start", () => {
    expect(elapsed(null, null)).toBe("");
  });
  it("shows seconds, then minutes", () => {
    expect(elapsed(1000, 5200)).toBe("4.2 s");
    expect(elapsed(0 + 1, 125_001)).toBe("2 min 5 s");
  });
  it("runs to now while not ended", () => {
    expect(elapsed(1000, null, 3000)).toBe("2.0 s");
  });
});

describe("settings", () => {
  it("turns INI keys into labels", () => {
    expect(settingLabel("SkipIntros")).toBe("Skip intros");
    expect(settingLabel("UILayoutTrace")).toBe("UI layout trace");
    expect(settingLabel("DumpObjectsKey")).toBe("Dump objects key");
    expect(settingLabel("Console")).toBe("Console");
  });
  it("drops the '1 = ' of switch comments", () => {
    expect(settingDescription(setting("SkipIntros", "1", "1 = skip the logo movies."))).toBe("Skip the logo movies.");
    expect(settingDescription(setting("DumpObjectsKey", "0x79", "virtual-key code."))).toBe("Virtual-key code.");
  });
  it("recognises switches and key codes", () => {
    expect(isSwitch(setting("Borderless", "1"))).toBe(true);
    expect(isSwitch(setting("Borderless", "7", "", "0"))).toBe(true);
    expect(isSwitch(setting("DumpObjectsKey", "0x79"))).toBe(false);
    expect(isSwitch(setting("SkipIntros", "1", "1 = skip the logo movies."))).toBe(true);
    expect(isSwitch(setting("MaxFPS", "0", "Highest frame rate, 0 = no limit."))).toBe(false);
    expect(isKeySetting(setting("DumpObjectsKey", "0x79"))).toBe(true);
    expect(isKeySetting(setting("Console", "0"))).toBe(false);
  });
  it("names function keys", () => {
    expect(keyName("0x79")).toBe("F10");
    expect(keyName("0X70")).toBe("F1");
    expect(keyName(" 0x7b ")).toBe("F12");
    expect(keyName("0")).toBe("Off");
    expect(keyName("0x41")).toBe("");
  });
});
