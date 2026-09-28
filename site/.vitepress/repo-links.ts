// Links in docs/ that leave the site: `../CONTRIBUTING.md`, `../sdk/include/...`,
// `../tools/sdk.py`. They work when the docs are read on GitHub, but the site
// only has the pages in docs/, so they become GitHub URLs on the default
// branch: blob/ for files, tree/ for folders.
//
// A link into docs/ that is a page of the site is left to VitePress, which
// also reports it when it is dead. A link to a repository path that does not
// exist is rewritten anyway (the file may come with a later commit) and listed
// as a warning.
import { statSync } from "node:fs";
import { dirname, isAbsolute, relative, resolve, sep } from "node:path";
import type { MarkdownRenderer } from "vitepress";

export interface RepoLinkOptions {
  /** The repository's root folder. */
  root: string;
  /** The site's source folder (docs/). */
  srcDir: string;
  /** `https://github.com/<owner>/<repo>` */
  url: string;
  branch: string;
  /** Whether a path relative to srcDir (as linked: `sdk.md`, `guide/`) is a page of the site. */
  isPage: (path: string) => boolean;
}

const warned = new Set<string>();

function kind(path: string): "file" | "dir" | undefined {
  try {
    return statSync(path).isDirectory() ? "dir" : "file";
  } catch {
    return undefined;
  }
}

const posix = (path: string) => path.split(sep).join("/");
const outside = (from: string, to: string) => {
  const rel = relative(from, to);
  return rel === ".." || rel.startsWith(".." + sep) || isAbsolute(rel);
};

/** The GitHub URL for `href` in the page at `file`, or undefined to leave it alone. */
export function repoUrl(href: string, file: string, o: RepoLinkOptions): string | undefined {
  // Only relative links: not "#anchor", "/site-path", "https:", "mailto:".
  if (!href || href.startsWith("#") || href.startsWith("/") || /^[a-z][a-z\d+.-]*:/i.test(href)) return undefined;
  const cut = href.search(/[?#]/);
  const path = cut < 0 ? href : href.slice(0, cut);
  const suffix = cut < 0 ? "" : href.slice(cut);
  if (!path) return undefined;
  const target = resolve(dirname(file), decodeURIComponent(path));
  const found = kind(target);

  if (!outside(o.srcDir, target)) {
    const inSite = posix(relative(o.srcDir, target)) + (path.endsWith("/") ? "/" : "");
    // Pages, missing pages (VitePress reports them) and assets stay as they are.
    if (o.isPage(inSite) || !found || (found === "file" && !target.endsWith(".md"))) return undefined;
  }
  if (outside(o.root, target)) return undefined; // VitePress reports it

  const inRepo = posix(relative(o.root, target));
  if (!found) {
    const key = `${inRepo} (linked from ${posix(relative(o.root, file))})`;
    if (!warned.has(key)) {
      warned.add(key);
      console.warn(`[repo-links] no such path in the repository: ${key}`);
    }
  }
  const tree = found ? found === "dir" : path.endsWith("/");
  return `${o.url}/${tree ? "tree" : "blob"}/${o.branch}/${inRepo}${suffix}`;
}

export function repoLinks(md: MarkdownRenderer, o: RepoLinkOptions): void {
  md.core.ruler.push("t3_repo_links", (state) => {
    const env = state.env as { realPath?: string; path?: string } | undefined;
    const file = env?.realPath ?? env?.path;
    if (!file) return;
    for (const block of state.tokens) {
      for (const token of block.children ?? []) {
        if (token.type !== "link_open") continue;
        const url = repoUrl(token.attrGet("href") ?? "", file, o);
        if (url) token.attrSet("href", url);
      }
    }
  });
}
