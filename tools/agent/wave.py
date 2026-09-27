#!/usr/bin/env python3
"""Lead only: run a wave of headless matching workers, each in its own git worktree.

    python tools/agent/wave.py --workers 8 [--functions 5] [--unit U] [--budget-usd 5] [--dry-run]

Each worker is `claude -p` on the t3-matcher agent prompt with the Sonnet
model, JSON output, and the guard settings (tools/agent/guard-settings.json,
rendered with this Python and absolute paths). It runs in a detached worktree
of HEAD under build/agent/worktrees/<wave>/, so tools/agent and .claude must
be committed. The tools find the shared state (claims, accepted records,
target objects) in the main checkout through git.

Not `--bare`: it skips hooks, including those passed with --settings, and so
would switch the guard off.

Results go to build/agent/waves/<wave>.json: per worker the exit status,
total_cost_usd, turns, duration and the JSON summary from its last line;
then totals. Claims a worker left behind are released; worktrees are removed
unless --keep-worktrees. --dry-run prints the commands and changes nothing.
"""

import argparse
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
import time
from pathlib import Path
from typing import Optional

from common import Claims, Project, atomic_write

AGENT_FILE = Path(".claude") / "agents" / "t3-matcher.md"


def system_prompt(main: Path) -> str:
    """The t3-matcher agent's instructions, without the frontmatter."""
    text = (main / AGENT_FILE).read_text(encoding="utf-8")
    return re.sub(r"\A---\n.*?\n---\n", "", text, flags=re.S).lstrip()


def settings(main: Path, python: str) -> str:
    """guard-settings.json with the hook run by this Python from the main checkout."""
    data = json.loads((main / "tools" / "agent" / "guard-settings.json").read_text(encoding="utf-8"))
    guard = (main / "tools" / "agent" / "hooks" / "guard.py").as_posix()
    for entry in data["hooks"]["PreToolUse"]:
        for hook in entry["hooks"]:
            hook["command"] = f'"{Path(python).as_posix()}" "{guard}"'
    return json.dumps(data, indent=2)


def summary_of(result: str) -> Optional[dict]:
    """The worker's final JSON line."""
    for line in reversed(result.strip().splitlines()):
        line = line.strip().strip("`")
        if line.startswith("{"):
            try:
                return json.loads(line)
            except ValueError:
                return None
    return None


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--workers", type=int, default=8)
    parser.add_argument("--functions", type=int, default=5, help="functions per worker")
    parser.add_argument("--unit", help="restrict the queue to a split unit (name or prefix)")
    parser.add_argument("--model", default="claude-sonnet-5")
    parser.add_argument("--budget-usd", type=float, help="--max-budget-usd per worker")
    parser.add_argument("--timeout", type=float, default=3 * 3600, help="seconds before a worker is stopped")
    parser.add_argument("--claude", default="claude", help="the Claude Code executable")
    parser.add_argument("--keep-worktrees", action="store_true")
    parser.add_argument("--allow-dirty", action="store_true",
                        help="run although tools/agent or .claude differ from HEAD")
    parser.add_argument("--dry-run", action="store_true", help="print the commands, change nothing")
    args = parser.parse_args()

    p = Project()
    main = p.main
    wave = time.strftime("%Y%m%d-%H%M%S", time.gmtime())
    wave_dir = p.state / "waves" / wave
    dirty = subprocess.run(["git", "status", "--porcelain", "--", "tools/agent", ".claude"], cwd=main,
                           capture_output=True, text=True).stdout.strip()
    if dirty and not args.allow_dirty:
        message = "tools/agent or .claude has uncommitted changes; the worktrees would not see them:\n" + dirty
        if not args.dry_run:
            sys.exit(message + "\n(commit them, or pass --allow-dirty)")
        print("warning: " + message)

    python = sys.executable
    prompt_file = wave_dir / "t3-matcher.md"
    settings_file = wave_dir / "settings.json"
    bin_dir = wave_dir / "bin"
    unit = f" --unit {args.unit}" if args.unit else ""
    workers = []
    for i in range(1, args.workers + 1):
        agent = f"{wave}-w{i:02d}"
        tree = p.state / "worktrees" / wave / f"w{i:02d}"
        prompt = (f"You are matching worker {agent}. Match up to {args.functions} functions from the queue, one "
                  f"at a time (`python tools/agent/next.py claim{unit}`), following your instructions. Then "
                  f"end with the JSON summary line.")
        cmd = [args.claude, "-p", prompt, "--model", args.model, "--output-format", "json",
               "--settings", str(settings_file), "--append-system-prompt-file", str(prompt_file),
               "--permission-mode", "dontAsk"]
        if args.budget_usd:
            cmd += ["--max-budget-usd", str(args.budget_usd)]
        workers.append({"agent": agent, "worktree": tree, "cmd": cmd})

    if args.dry_run:
        print(f"# wave {wave}: {args.workers} workers x {args.functions} functions, model {args.model}")
        print(f"# would write {prompt_file} (from {AGENT_FILE}), {settings_file} (guard hook: {python}),")
        print(f"#   and {bin_dir}/python -> {python}")
        for w in workers:
            print(f"git -C {shlex.quote(str(main))} worktree add --detach {shlex.quote(str(w['worktree']))} HEAD")
            print(f"(cd {shlex.quote(str(w['worktree']))} && T3_AGENT_ID={w['agent']} PATH={bin_dir}{os.pathsep}$PATH "
                  + " ".join(shlex.quote(c) for c in w["cmd"]) + ")")
        return

    wave_dir.mkdir(parents=True, exist_ok=True)
    atomic_write(prompt_file, system_prompt(main))
    atomic_write(settings_file, settings(main, python))
    bin_dir.mkdir(exist_ok=True)
    if os.name != "nt":  # workers run `python tools/agent/...`: make `python` this interpreter
        shim = bin_dir / "python"
        if not shim.exists():
            shim.symlink_to(python)
        path = f"{bin_dir}{os.pathsep}{os.environ.get('PATH', '')}"
    else:
        path = f"{Path(python).parent}{os.pathsep}{os.environ.get('PATH', '')}"

    started = time.time()
    procs = []
    for w in workers:
        subprocess.run(["git", "worktree", "add", "--detach", str(w["worktree"]), "HEAD"], cwd=main, check=True,
                       capture_output=True)
        env = dict(os.environ, T3_AGENT_ID=w["agent"], T3_AGENT_WAVE=wave, PATH=path)
        out = open(wave_dir / f"{w['agent']}.out.json", "w", encoding="utf-8")
        err = open(wave_dir / f"{w['agent']}.err.txt", "w", encoding="utf-8")
        procs.append((w, subprocess.Popen(w["cmd"], cwd=w["worktree"], env=env, stdout=out, stderr=err), out, err))
        print(f"started {w['agent']} in {w['worktree']}")

    results = []
    for w, proc, out, err in procs:
        try:
            proc.wait(timeout=max(1.0, started + args.timeout - time.time()))
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait()
        out.close()
        err.close()
        raw = (wave_dir / f"{w['agent']}.out.json").read_text(encoding="utf-8", errors="replace")
        try:
            data = json.loads(raw)
        except ValueError:
            data = {}
        released = [c["addr"] for c in Claims(p).all() if c.get("agent") == w["agent"]
                    and Claims(p).release(int(c["addr"], 16), w["agent"])]
        results.append({
            "agent": w["agent"], "worktree": str(w["worktree"]), "returncode": proc.returncode,
            "cost_usd": data.get("total_cost_usd"), "turns": data.get("num_turns"),
            "duration_ms": data.get("duration_ms"), "is_error": data.get("is_error", True),
            "session_id": data.get("session_id"), "summary": summary_of(data.get("result", "") or ""),
            "released_claims": released,
        })
        if not args.keep_worktrees:
            subprocess.run(["git", "worktree", "remove", "--force", str(w["worktree"])], cwd=main,
                           capture_output=True)

    matched = sum(len((r["summary"] or {}).get("matched", [])) for r in results)
    deferred = sum(len((r["summary"] or {}).get("deferred", [])) for r in results)
    cost = sum(r["cost_usd"] or 0 for r in results)
    report = {
        "wave": wave, "model": args.model, "workers": args.workers, "functions_per_worker": args.functions,
        "unit": args.unit, "started": started, "finished": time.time(), "total_cost_usd": round(cost, 4),
        "matched": matched, "deferred": deferred,
        "cost_per_match_usd": round(cost / matched, 4) if matched else None,
        "needs": sorted({n for r in results for n in (r["summary"] or {}).get("needs", [])}),
        "idioms": sorted({n for r in results for n in (r["summary"] or {}).get("idioms", [])}),
        "results": results,
    }
    path = p.state / "waves" / f"{wave}.json"
    atomic_write(path, json.dumps(report, indent=1))
    if not args.keep_worktrees:
        shutil.rmtree(p.state / "worktrees" / wave, ignore_errors=True)
    print(f"wave {wave}: {matched} matched, {deferred} deferred, ${cost:.2f}; {path}")


if __name__ == "__main__":
    main()
