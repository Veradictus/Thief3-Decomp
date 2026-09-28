<script lang="ts">
  // A path setting: text field, Browse, detected candidates, and a live check.
  import Icon from "./Icon.svelte";
  import { api, pick, errorText, type Candidate, type CheckResult } from "$lib/api";

  let {
    label,
    hint = "",
    value = $bindable(null),
    candidates = [],
    directory = true,
    optional = false,
    check,
    ok = $bindable(false),
    action,
  }: {
    label: string;
    hint?: string;
    value?: string | null;
    candidates?: Candidate[];
    directory?: boolean;
    optional?: boolean;
    check: (path: string) => Promise<CheckResult>;
    ok?: boolean;
    action?: { label: string; href: string };
  } = $props();

  let result = $state<CheckResult | null>(null);
  let checking = $state(false);
  let timer: ReturnType<typeof setTimeout> | undefined;
  let serial = 0;

  async function run(path: string | null) {
    const mine = ++serial;
    if (!path) {
      result = null;
      ok = false;
      return;
    }
    checking = true;
    try {
      const r = await check(path);
      if (mine === serial) result = r;
    } catch (e) {
      if (mine === serial) result = { ok: false, message: errorText(e) };
    } finally {
      if (mine === serial) {
        checking = false;
        ok = result?.ok ?? false;
      }
    }
  }

  $effect(() => {
    const path = value;
    clearTimeout(timer);
    timer = setTimeout(() => void run(path), 250);
    return () => {
      clearTimeout(timer);
    };
  });

  async function browse() {
    const chosen = await pick(directory, `Choose ${label}`);
    if (chosen) value = chosen;
  }

  const others = $derived(candidates.filter((c) => c.path !== value));
</script>

<div class="field card">
  <div class="head">
    <div class="grow">
      <h3>
        {label}
        {#if optional}<span class="faint opt">optional</span>{/if}
      </h3>
      {#if hint}<p class="muted hint">{hint}</p>{/if}
    </div>
    {#if checking}
      <span class="badge">Checking…</span>
    {:else if result}
      <span class="badge" class:ok={result.ok} class:err={!result.ok}>
        <Icon name={result.ok ? "check" : "alert"} size={13} />{result.ok ? "OK" : "Problem"}
      </span>
    {:else if !optional}
      <span class="badge warn">Required</span>
    {/if}
  </div>
  <div class="row">
    <input
      type="text"
      spellcheck="false"
      placeholder={directory ? "Folder path" : "Program path"}
      value={value ?? ""}
      oninput={(e) => (value = e.currentTarget.value.trim() || null)}
    />
    <button class="btn" onclick={browse}><Icon name="folder" />Browse</button>
  </div>
  {#if result}
    <p class="result" class:bad={!result.ok}>
      {result.message}{#if result.detail}<span class="faint"> · {result.detail}</span>{/if}
    </p>
  {/if}
  {#if others.length}
    <div class="found">
      <span class="faint">Found:</span>
      {#each others as c (c.path)}
        <button class="chip" title={c.path} onclick={() => (value = c.path)}>
          <span class="src">{c.source}</span><span class="mono">{c.path}</span>
        </button>
      {/each}
    </div>
  {/if}
  {#if action && !ok}
    <p class="action"><button class="link" onclick={() => api.openLink(action.href)}>{action.label}</button></p>
  {/if}
</div>

<style>
  .field {
    padding: 16px 18px;
    display: flex;
    flex-direction: column;
    gap: 10px;
  }

  .head {
    display: flex;
    align-items: flex-start;
    gap: 12px;
  }

  .hint {
    margin-top: 2px;
    font-size: 13px;
  }

  .opt {
    font-family: var(--sans);
    font-size: 12px;
    font-weight: 400;
    margin-left: 6px;
  }

  .result {
    font-size: 13px;
    color: var(--ok);
  }

  .result.bad {
    color: var(--err);
  }

  .found {
    display: flex;
    flex-wrap: wrap;
    align-items: center;
    gap: 6px;
    font-size: 12.5px;
  }

  .chip {
    display: inline-flex;
    gap: 7px;
    align-items: center;
    max-width: 100%;
    padding: 3px 9px;
    border-radius: 99px;
    border: 1px solid var(--line-2);
    background: var(--panel-2);
    cursor: pointer;
    overflow: hidden;
  }

  .chip:hover {
    border-color: var(--accent);
  }

  .chip .src {
    color: var(--accent-2);
    flex: none;
  }

  .chip .mono {
    color: var(--muted);
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
    font-size: 12px;
  }

  .action {
    font-size: 13px;
  }

  .link {
    padding: 0;
    border: 0;
    background: none;
    color: var(--accent-2);
    text-decoration: underline;
    cursor: pointer;
  }
</style>
