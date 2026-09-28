// `yarn tauri`: the Tauri CLI, with the Rust toolchain it needs on Windows.
//
// Tauri builds with Rust's MSVC toolchain on Windows. A GNU one
// (x86_64-pc-windows-gnu) fails on the windows crates unless MinGW's
// dlltool.exe is on PATH ("error calling dlltool 'dlltool.exe': program not
// found"). When rustup would build src-tauri/ with such a toolchain, the CLI
// runs with the MSVC toolchain of the same channel instead, through
// RUSTUP_TOOLCHAIN; rustup installs it on first use. Everywhere else, and when
// RUSTUP_TOOLCHAIN is already set, the CLI runs unchanged.
import { execFileSync } from "node:child_process";
import { existsSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import cli from "@tauri-apps/cli";

/** The MSVC toolchain to build with instead of the active one, if it is needed. */
function msvcToolchain() {
  if (process.platform !== "win32" || process.env.RUSTUP_TOOLCHAIN) return undefined;
  let active;
  try {
    // "stable-x86_64-pc-windows-gnu (default)"
    active = execFileSync("rustup", ["show", "active-toolchain"], {
      cwd: fileURLToPath(new URL("../src-tauri/", import.meta.url)),
      encoding: "utf8",
      stdio: ["ignore", "pipe", "ignore"],
    });
  } catch {
    return undefined; // Rust without rustup, or none: nothing to switch to
  }
  const name = active.split(/\s/)[0] ?? "";
  if (!name.endsWith("-pc-windows-gnu")) return undefined;
  const dirs = (process.env.PATH ?? "").split(path.delimiter).filter(Boolean);
  if (dirs.some((dir) => existsSync(path.join(dir, "dlltool.exe")))) return undefined; // GNU can build
  return name.replace(/-gnu$/, "-msvc");
}

const toolchain = msvcToolchain();
if (toolchain) {
  console.log(`Rust: using ${toolchain}; the active GNU toolchain cannot build Tauri (see docs/launcher.md).`);
  process.env.RUSTUP_TOOLCHAIN = toolchain;
}

cli.run(process.argv.slice(2), "yarn tauri").catch((error) => {
  cli.logError(error instanceof Error ? error.message : String(error));
  process.exit(1);
});
