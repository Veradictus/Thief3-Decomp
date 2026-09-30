import { existsSync } from "node:fs";
import { isAbsolute, relative } from "node:path";
import { fileURLToPath } from "node:url";
import type { Plugin } from "vite";
import { defineConfig } from "vitepress";
import { repoLinks } from "./repo-links";

const repo = "https://github.com/Veradictus/Thief3-Decomp";
const root = fileURLToPath(new URL("../../", import.meta.url));
const srcDir = fileURLToPath(new URL("../../docs/", import.meta.url));
const configFile = fileURLToPath(import.meta.url);

/**
 * Whether `file` is inside docs/. Compared as paths, not strings: on Windows
 * Vite spells ids with forward slashes and fileURLToPath with backslashes.
 */
function inSrcDir(file: string): boolean {
  const rel = relative(srcDir, file);
  return rel !== "" && !rel.startsWith("..") && !isAbsolute(rel);
}

/**
 * The pages are compiled into modules that import `vue` and
 * `vue/server-renderer`. Node-style resolution looks for those next to the
 * page, in docs/, where there is no node_modules: resolve them from site/.
 */
const resolveFromSite: Plugin = {
  name: "t3-resolve-from-site",
  enforce: "pre",
  resolveId(id, importer, options) {
    if (!importer || !inSrcDir(importer) || !/^[a-z@][\w@./-]*$/i.test(id)) return null;
    return this.resolve(id, configFile, { ...options, skipSelf: true });
  },
};

// Markdown files in docs/ that are not pages of the site (none so far). Links to
// them go to GitHub instead.
const srcExclude: string[] = [];

/** Whether a path relative to docs/, as a link spells it, is a page of the site. */
function isPage(path: string): boolean {
  const candidates = path.endsWith(".md")
    ? [path]
    : path.endsWith("/") || path === ""
      ? [`${path}index.md`]
      : [`${path.replace(/\.html$/, "")}.md`, `${path}/index.md`];
  return candidates.some((c) => !srcExclude.includes(c) && existsSync(srcDir + c));
}

export default defineConfig({
  title: "T3SDK",
  description: "Mods, fixes and a mod loader for Thief: Deadly Shadows, and a matching decompilation of the game.",
  lang: "en-US",
  base: "/Thief3-Decomp/",
  srcDir: "../docs",
  srcExclude,
  cleanUrls: true,
  appearance: "dark",
  sitemap: { hostname: "https://veradictus.github.io/Thief3-Decomp/" },
  head: [
    ["link", { rel: "icon", type: "image/svg+xml", href: "/Thief3-Decomp/logo.svg" }],
    ["meta", { name: "theme-color", content: "#0d0e11" }],
  ],

  vite: {
    // site/public holds the logo; the pages come from docs/.
    publicDir: fileURLToPath(new URL("../public", import.meta.url)),
    plugins: [resolveFromSite],
  },

  markdown: {
    config: (md) => repoLinks(md, { root, srcDir, url: repo, branch: "main", isPage }),
  },

  themeConfig: {
    logo: "/logo.svg",
    siteTitle: "T3SDK",
    nav: [
      { text: "Play", link: "/guide/getting-started", activeMatch: "^/guide/" },
      { text: "Make mods", link: "/modding/first-mod", activeMatch: "^/modding/" },
      { text: "How it works", link: "/game/", activeMatch: "^/game/" },
      { text: "API", link: "/reference/api", activeMatch: "^/reference/" },
      { text: "Decomp", link: "/decomp/", activeMatch: "^/decomp/" },
      { text: "Download", link: `${repo}/releases/latest` },
    ],
    sidebar: [
      {
        text: "Player guide",
        items: [
          { text: "Getting started", link: "/guide/getting-started" },
          { text: "Playing with T3SDK", link: "/guide/playing" },
          { text: "Settings explained", link: "/guide/settings" },
          { text: "Installing mods", link: "/guide/mods" },
          { text: "Save backups", link: "/guide/saves" },
          { text: "Other mods and tools", link: "/guide/compatibility" },
          { text: "Troubleshooting", link: "/guide/troubleshooting" },
          { text: "FAQ", link: "/guide/faq" },
          { text: "Glossary", link: "/guide/glossary" },
        ],
      },
      {
        text: "Mod author guide",
        items: [
          { text: "Your first mod", link: "/modding/first-mod" },
          { text: "The mod lifecycle", link: "/modding/lifecycle" },
          { text: "Packaging", link: "/modding/packaging" },
          { text: "Content and texture packs", link: "/modding/content-packs" },
          { text: "Publishing to the mod index", link: "/modding/publishing" },
          { text: "Map editing", link: "/modding/maps" },
          {
            text: "Cookbook",
            link: "/modding/cookbook/",
            collapsed: true,
            items: [
              { text: "Run code every frame", link: "/modding/cookbook/every-frame" },
              { text: "Write to the log", link: "/modding/cookbook/logging" },
              { text: "Find and inspect objects", link: "/modding/cookbook/objects" },
              { text: "Hook a game function", link: "/modding/cookbook/hooks" },
              { text: "Give your mod its own settings", link: "/modding/cookbook/settings" },
              { text: "Replace game files with a content pack", link: "/modding/cookbook/content" },
              { text: "Map edit recipes", link: "/modding/cookbook/maps" },
              { text: "Debug a mod", link: "/modding/cookbook/debugging" },
              { text: "Play well with other mods", link: "/modding/cookbook/compatibility" },
            ],
          },
        ],
      },
      {
        text: "Game and engine",
        items: [
          { text: "How the game works", link: "/game/" },
          { text: "Architecture", link: "/game/architecture" },
          { text: "Objects, names and classes", link: "/game/objects" },
          { text: "The gamesys property system", link: "/game/gamesys" },
          { text: "Levels and maps", link: "/game/levels" },
          { text: "The install and its files", link: "/game/files" },
          { text: "INI files and settings", link: "/game/config" },
          { text: "The game loop and level changes", link: "/game/runtime" },
          { text: "Display, UI and HUD", link: "/game/display" },
          { text: "Console commands", link: "/game/console" },
        ],
      },
      {
        text: "Reference",
        items: [
          { text: "Mod API", link: "/reference/api" },
          { text: "Mod packages (.t3mod)", link: "/mods" },
          { text: "SDK settings and tools", link: "/sdk" },
          { text: "Launcher", link: "/launcher" },
        ],
      },
      {
        text: "Decomp handbook",
        items: [
          { text: "Overview", link: "/decomp/" },
          { text: "Setting up the workbench", link: "/decomp/setup" },
          { text: "Reverse engineering a function", link: "/decomp/reverse-engineering" },
          { text: "Naming and documenting", link: "/decomp/naming" },
          { text: "Your first match", link: "/decomp/first-match" },
          { text: "Techniques and patterns", link: "/decomp/techniques" },
        ],
      },
      {
        text: "Engineering",
        collapsed: false,
        items: [
          { text: "Status and next steps", link: "/handoff" },
          { text: "Engine internals", link: "/engine" },
          { text: "The target binary", link: "/target" },
          { text: "Matching decompilation", link: "/matching" },
          { text: "Tiered agent workflow", link: "/agent-workflow" },
          { text: "Progress on decomp.dev", link: "/decomp-dev" },
          { text: "Assets and formats", link: "/assets" },
          { text: "Research: LLM matching", link: "/research/llm-matching" },
          { text: "This site", link: "/site" },
        ],
      },
    ],
    outline: { level: [2, 3] },
    search: { provider: "local" },
    editLink: {
      // Runs in the browser: no references to this module's variables.
      pattern: ({ filePath }) =>
        filePath === "reference/api.md"
          ? "https://github.com/Veradictus/Thief3-Decomp/edit/master/sdk/include/t3sdk/t3sdk.h"
          : `https://github.com/Veradictus/Thief3-Decomp/edit/master/docs/${filePath}`,
      text: "Edit this page on GitHub",
    },
    socialLinks: [
      { icon: "github", link: repo },
      { icon: "discord", link: "https://discord.gg/eaJkC5C6WJ" },
    ],
    footer: {
      message:
        "A fan project, not affiliated with or endorsed by Ion Storm, Eidos or the owners of the Thief series. Buy the game.",
    },
  },
});
