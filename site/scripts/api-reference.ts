// Writes docs/reference/api.md from sdk/include/t3sdk/t3sdk.h.
//
//   node scripts/api-reference.ts           write the page (when it changed)
//   node scripts/api-reference.ts --check   exit 1 when the committed page is stale
//
// The page is committed so that docs/ reads the same on GitHub; CI runs the
// check. The parser knows the header's conventions, not C:
//   - the comment at the top of the file is the overview;
//   - `#define NAME value /* text */` lines are the macros;
//   - a typedef takes the comment block right above it (preprocessor lines
//     may sit in between);
//   - inside `struct T3SdkApi`, blank lines separate groups. A group's first
//     comment describes the group when two or more members follow it before
//     the next comment; any other comment describes the member below it. A
//     comment after a member on the same line is part of that member's text;
//   - "since API version N" (or "since version N") in a member's text is shown
//     as the version that added it.
import { readFileSync, writeFileSync } from "node:fs";
import { dirname, join, relative } from "node:path";
import { fileURLToPath } from "node:url";

const site = join(dirname(fileURLToPath(import.meta.url)), "..");
const repo = join(site, "..");
const headerPath = join(repo, "sdk/include/t3sdk/t3sdk.h");
const outPath = join(repo, "docs/reference/api.md");

interface Macro {
  name: string;
  values: { value: string; when: string }[];
  text: string;
}

interface Typedef {
  name: string;
  decls: { decl: string; when: string }[];
  text: string;
}

interface Member {
  name: string;
  signature: string;
  text: string;
}

interface Group {
  intro: string;
  members: Member[];
}

interface Header {
  overview: string;
  macros: Macro[];
  typedefs: Typedef[];
  groups: Group[];
}

// ---- parsing -----------------------------------------------------------------

/** The text of a comment's lines, without the comment markers and the leading " * ". */
function commentText(lines: string[]): string {
  const body = lines
    .join("\n")
    .replace(/^\s*\/\*+/, "")
    .replace(/\*+\/\s*$/, "")
    .split("\n")
    .map((line) => line.replace(/^\s*\/\/\s?/, "").replace(/^\s*\* ?/, "").trimEnd());
  while (body.length && body[0]?.trim() === "") body.shift();
  while (body.length && body.at(-1)?.trim() === "") body.pop();
  // Continuation lines of a comment that starts on its first line ("/* text")
  // carry the same indentation as the text; take out what they share.
  const indents = body.slice(1).filter((l) => l.trim()).map((l) => /^ */.exec(l)?.[0].length ?? 0);
  const common = indents.length ? Math.min(...indents) : 0;
  return body.map((l, i) => (i === 0 ? l.trim() : l.slice(common))).join("\n");
}

/** Splits `code; /* text *\/` into the code and the trailing comment's text. */
function splitTrailing(line: string): { code: string; text: string } {
  const m = /^(.*?;|#define\s.*?)\s*(\/\*(.*?)\*\/|\/\/(.*))\s*$/.exec(line);
  if (!m) return { code: line.trim(), text: "" };
  return { code: (m[1] ?? "").trim(), text: (m[3] ?? m[4] ?? "").trim() };
}

/** Reads the comment that starts at lines[i]; returns its text and the index after it. */
function readComment(lines: string[], i: number): { text: string; next: number } {
  const first = lines[i] ?? "";
  if (first.trim().startsWith("//")) {
    const block: string[] = [];
    while (lines[i]?.trim().startsWith("//")) block.push(lines[i++] ?? "");
    return { text: commentText(block), next: i };
  }
  const block: string[] = [];
  while (i < lines.length) {
    const line = lines[i++] ?? "";
    block.push(line);
    if (line.includes("*/")) break;
  }
  return { text: commentText(block), next: i };
}

const isComment = (line: string) => /^\s*(\/\*|\/\/)/.test(line);

/** `ret(T3SDK_CALL* Name)(params)` as `ret Name(params)`. */
function prototype(code: string): { name: string; signature: string } | null {
  const fn = /^(.*?)\(\s*T3SDK_CALL\s*\*\s*(\w+)\s*\)\s*\((.*)\)\s*;$/.exec(code);
  if (fn) {
    const ret = (fn[1] ?? "").replace(/^typedef\s+/, "").trim();
    return { name: fn[2] ?? "", signature: `${ret} ${fn[2] ?? ""}(${fn[3] ?? ""});` };
  }
  const field = /^(.*?\S)\s*\b(\w+)\s*;$/.exec(code);
  if (field) return { name: field[2] ?? "", signature: code };
  return null;
}

function parse(source: string): Header {
  const lines = source.replace(/\r\n/g, "\n").split("\n");
  const header: Header = { overview: "", macros: [], typedefs: [], groups: [] };
  const conditions: string[] = []; // "C++" or "C" while inside #ifdef __cplusplus / #else
  let pending = ""; // the comment waiting for the declaration below it
  let i = 0;

  const first = readComment(lines, 0);
  if (isComment(lines[0] ?? "")) {
    // The first line is the header's title ("T3SDK mod API."); the page has its own.
    header.overview = first.text.replace(/^[^\n]{0,40}\n\n/, "");
    i = first.next;
  }

  while (i < lines.length) {
    const line = lines[i] ?? "";
    const trimmed = line.trim();

    if (trimmed === "") {
      pending = "";
      i++;
      continue;
    }
    if (isComment(line)) {
      const c = readComment(lines, i);
      pending = c.text;
      i = c.next;
      continue;
    }
    if (trimmed.startsWith("#")) {
      if (/^#\s*ifdef\s+__cplusplus/.test(trimmed)) conditions.push("C++");
      else if (/^#\s*if/.test(trimmed)) conditions.push("");
      else if (/^#\s*else/.test(trimmed)) conditions.push(conditions.pop() === "C++" ? "C" : "");
      else if (/^#\s*endif/.test(trimmed)) conditions.pop();
      const define = /^#\s*define\s+(\w+)(?:\s+(.*))?$/.exec(trimmed);
      if (define && !/_H$/.test(define[1] ?? "")) {
        const { code, text } = splitTrailing(trimmed);
        const value = code.replace(/^#\s*define\s+\w+\s*/, "");
        const when = conditions.at(-1) ?? "";
        const known = header.macros.find((m) => m.name === define[1]);
        if (known) {
          known.values.push({ value, when });
          if (!known.text) known.text = text;
        } else {
          header.macros.push({ name: define[1] ?? "", values: [{ value, when }], text: text || pending });
        }
      }
      i++;
      continue;
    }
    if (/^typedef\s+struct\s+T3SdkApi\s*\{/.test(trimmed)) {
      i = parseApi(lines, i + 1, header);
      pending = "";
      continue;
    }
    if (trimmed.startsWith("typedef")) {
      const { code, text } = splitTrailing(trimmed);
      const fn = prototype(code);
      const plain = /^typedef\s+(.*?)\s+(\w+)\s*;$/.exec(code);
      const name = fn?.name ?? plain?.[2] ?? "";
      const decl = code;
      const when = conditions.at(-1) ?? "";
      const known = header.typedefs.find((t) => t.name === name);
      if (known) known.decls.push({ decl, when });
      else header.typedefs.push({ name, decls: [{ decl, when }], text: [pending, text].filter(Boolean).join("\n\n") });
      // A comment above an #ifdef'd pair of typedefs covers both.
      if (!conditions.at(-1)) pending = "";
      i++;
      continue;
    }
    i++; // anything else (includes, namespaces) is not documented
  }
  return header;
}

/** Parses the members of T3SdkApi from lines[i] up to its closing brace; returns the index after it. */
function parseApi(lines: string[], i: number, header: Header): number {
  // Items of the current blank-line-separated block, in order.
  type Item = { comment: string } | { code: string; text: string };
  let block: Item[] = [];

  const flush = () => {
    if (!block.length) return;
    const group: Group = { intro: "", members: [] };
    let start = 0;
    const firstItem = block[0];
    if (firstItem && "comment" in firstItem) {
      let following = 0;
      for (const item of block.slice(1)) {
        if ("comment" in item) break;
        following++;
      }
      if (following >= 2) {
        group.intro = firstItem.comment;
        start = 1;
      }
    }
    let pending = "";
    for (const item of block.slice(start)) {
      if ("comment" in item) {
        pending = item.comment;
        continue;
      }
      const proto = prototype(item.code);
      if (!proto) throw new Error(`t3sdk.h: cannot read the T3SdkApi member "${item.code}"`);
      group.members.push({ ...proto, text: [pending, item.text].filter(Boolean).join("\n\n") });
      pending = "";
    }
    header.groups.push(group);
    block = [];
  };

  while (i < lines.length) {
    const line = lines[i] ?? "";
    const trimmed = line.trim();
    if (trimmed.startsWith("}")) {
      flush();
      return i + 1;
    }
    if (trimmed === "") {
      flush();
      i++;
    } else if (isComment(line)) {
      const c = readComment(lines, i);
      block.push({ comment: c.text });
      i = c.next;
    } else {
      // A member may span lines: read up to its semicolon.
      let code = trimmed;
      while (!splitTrailing(code).code.endsWith(";") && i + 1 < lines.length) code += " " + (lines[++i] ?? "").trim();
      const { code: decl, text } = splitTrailing(code);
      block.push({ code: decl, text });
      i++;
    }
  }
  throw new Error("t3sdk.h: struct T3SdkApi has no closing brace");
}

// ---- markdown ------------------------------------------------------------------

/**
 * Comment text as markdown: paragraphs are joined into lines, lines indented
 * by four or more spaces become code blocks, a line starting with "Word:"
 * after a full stop starts a new paragraph, and identifiers get code spans.
 */
function markdown(text: string, known: Set<string>): string {
  const out: string[] = [];
  let paragraph: string[] = [];
  let code: string[] = [];
  const endParagraph = () => {
    if (paragraph.length) out.push(inline(paragraph.join(" "), known));
    paragraph = [];
  };
  const endCode = () => {
    if (code.length) out.push("```c\n" + code.join("\n") + "\n```");
    code = [];
  };
  for (const line of text.split("\n")) {
    if (/^ {4}/.test(line) && line.trim()) {
      endParagraph();
      code.push(line.slice(4));
      continue;
    }
    endCode();
    const label = /^([A-Z][a-z]+):\s+(.*)$/.exec(line);
    if (!line.trim()) {
      endParagraph();
    } else if (label && (!paragraph.length || /[.)]$/.test(paragraph.at(-1) ?? ""))) {
      endParagraph();
      paragraph.push(`**${label[1] ?? ""}:** ${label[2] ?? ""}`);
    } else {
      paragraph.push(line.trim());
    }
  }
  endParagraph();
  endCode();
  return out.join("\n\n");
}

/** Code spans for identifiers, calls, string literals and file names; the rest escaped for Vue. */
function inline(text: string, known: Set<string>): string {
  const names = [...known].sort((a, b) => b.length - a.length).join("|");
  const token = new RegExp(
    [
      "`[^`]*`", // already code
      '"[^"]*"', // string literal
      "\\*\\*[^*]+\\*\\*", // bold label
      "\\b[A-Za-z_]\\w*(?:->\\w+)+(?:\\([^()]*\\))?", // api->Member(...)
      "\\b[A-Za-z_]\\w*::\\w+", // Type::member
      "\\b[A-Za-z_]\\w*\\([^()]*\\)", // Call(...)
      "\\b[A-Z][A-Z0-9]*_[A-Z0-9_]+\\b", // MACRO_NAME
      "\\b[\\w-]+\\.(?:hpp|h|log|ini|dll)\\b", // file names: t3sdk.h, T3SDK.log
      `\\b(?:${names})\\b\\*?`, // known identifiers, with a pointer star
    ].join("|"),
    "g",
  );
  let out = "";
  let last = 0;
  for (const m of text.matchAll(token)) {
    out += escape(text.slice(last, m.index));
    const t = m[0];
    out += t.startsWith("`") || t.startsWith("**") ? t : "`" + t + "`";
    last = m.index + t.length;
  }
  return out + escape(text.slice(last));
}

const escape = (s: string) => s.replace(/</g, "&lt;").replace(/\{\{/g, "&#123;&#123;");

/** Ends a description with a full stop, as the header's longer comments do. */
const sentence = (s: string) => (!s || /[.!?:)]$/.test(s) ? s : s + ".");

/**
 * Parameter names worth a code span in a member's text: camelCase names and
 * short ones (`buf`, `cls`), not those that read as words (`size`, `object`).
 */
function paramNames(signature: string): string[] {
  const params = /\((.*)\)/.exec(signature)?.[1] ?? "";
  return params
    .split(",")
    .map((p) => /(\w+)\s*$/.exec(p.trim())?.[1] ?? "")
    .filter((n) => /[a-z][A-Z]/.test(n) || (n.length > 0 && n.length <= 3 && n !== "int"));
}

function render(h: Header, headerRel: string): string {
  const members = h.groups.flatMap((g) => g.members);
  const known = new Set<string>([
    "NULL",
    "T3Mod_Init",
    "T3Mod_Shutdown",
    ...h.typedefs.map((t) => t.name),
    ...h.macros.map((m) => m.name),
    ...members.map((m) => m.name).filter((n) => /^[A-Z]/.test(n)),
  ]);
  const md = (s: string, extra: string[] = []) => markdown(s, extra.length ? new Set([...known, ...extra]) : known);
  // "Since API version 2." in a comment becomes a marker after the member's text.
  const sinceRe = /\s*\(?\bsince (?:API )?version (\d+)\)?\.?/i;
  const since = (s: string) => sinceRe.exec(s)?.[1];
  const withoutSince = (s: string) => s.replace(sinceRe, "").trim();
  const version = h.macros.find((m) => m.name === "T3SDK_API_VERSION")?.values[0]?.value ?? "?";
  const out: string[] = [];

  out.push(
    "---",
    "outline: [2, 3]",
    "---",
    "",
    "<!-- Generated by site/scripts/api-reference.ts from sdk/include/t3sdk/t3sdk.h.",
    "     Do not edit: change the header, then run `yarn api` in site/. -->",
    "",
    "# Mod API reference",
    "",
    `The C API that T3SDK hands to every mod, as declared in [t3sdk.h](${headerRel}t3sdk.h). ` +
      `This page is generated from that header's comments (API version ${version}). ` +
      `The optional C++ header [unreal.hpp](${headerRel}unreal.hpp) has the engine's memory layouts and fixed ` +
      "addresses for advanced use; they are specific to the supported game build.",
    "",
    "How a mod uses these calls over the game's lifetime is in [The mod lifecycle](../modding/lifecycle.md).",
    "",
    "## Overview",
    "",
    md(h.overview),
    "",
  );

  out.push("## T3SdkApi", "", "`T3Mod_Init` receives a pointer to this table. Call through it: `api->Log(...)`.", "");
  for (const group of h.groups) {
    // "Callbacks; each returns ..." is titled "Callbacks" and described from "Each returns ...".
    const lead = /^([^;:(.]{1,40})([;:(.])\s*/.exec(group.intro);
    const title = lead?.[1]?.trim() ?? group.members.map((m) => m.name).join(", ");
    let intro = group.intro;
    if (lead && lead[2] !== "(") intro = intro.slice(lead[0].length).replace(/^\w/, (c) => c.toUpperCase());
    intro = withoutSince(intro);
    out.push(`### ${title}`, "");
    if (intro) out.push(md(intro), "");
    out.push("```c", ...group.members.map((m) => m.signature), "```", "");
    const described = group.members.filter((m) => m.text || since(group.intro));
    for (const m of described) {
      const v = since(m.text) ?? since(group.intro);
      const own = withoutSince(m.text);
      const text = own ? sentence(md(own, paramNames(m.signature)).replace(/\n\n/g, " ")) : "";
      const parts = [text, v ? `*Since API version ${v}.*` : ""].filter(Boolean).join(" ");
      out.push(`- **\`${m.name}\`**: ${parts}`);
    }
    if (described.length) out.push("");
  }

  out.push("## Types", "");
  for (const t of h.typedefs) {
    out.push(`### ${t.name}`, "", "```c");
    for (const d of t.decls) out.push(d.when ? `${d.decl} /* ${d.when} */` : d.decl);
    out.push("```", "");
    if (t.text) out.push(md(t.text), "");
  }

  out.push("## Macros", "", "| Macro | Value | Meaning |", "|---|---|---|");
  for (const m of h.macros) {
    const values = m.values
      .map((v) => (v.value ? "`" + v.value.replace(/\|/g, "\\|") + "`" : "empty") + (v.when ? ` (${v.when})` : ""))
      .join(", ");
    out.push(`| \`${m.name}\` | ${values} | ${md(m.text).replace(/\n\n/g, " ").replace(/\|/g, "\\|")} |`);
  }
  out.push("");
  return out.join("\n");
}

// ---- main ----------------------------------------------------------------------

const headerRel = relative(dirname(outPath), dirname(headerPath)).replace(/\\/g, "/") + "/";
const page = render(parse(readFileSync(headerPath, "utf8")), headerRel);
let current = "";
try {
  current = readFileSync(outPath, "utf8");
} catch {
  // not written yet
}

if (process.argv.includes("--check")) {
  if (current !== page) {
    console.error("docs/reference/api.md is out of date with sdk/include/t3sdk/t3sdk.h: run `yarn api` in site/.");
    process.exit(1);
  }
  console.log("docs/reference/api.md is up to date.");
} else if (current !== page) {
  writeFileSync(outPath, page);
  console.log("wrote docs/reference/api.md");
}
