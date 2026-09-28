<script lang="ts">
  // Profiles: a saved load order and set of enabled mods. The active profile
  // follows every change; switching applies another one.
  import Icon from "$components/Icon.svelte";
  import type { ModList } from "$lib/api";
  import { mods, profile } from "$lib/mods.svelte";

  let { list }: { list: ModList } = $props();

  let mode = $state<"idle" | "saveAs" | "rename" | "delete">("idle");
  let name = $state("");
  let target = $state("");

  const others = $derived(list.profiles.filter((p) => p !== list.profile));
  const clash = $derived(
    list.profiles.some(
      (p) => p.toLowerCase() === name.trim().toLowerCase() && !(mode === "rename" && p === list.profile),
    ),
  );
  const valid = $derived(name.trim().length > 0 && name.trim().length <= 40 && !clash);

  function start(next: typeof mode) {
    mode = next;
    name = next === "rename" ? list.profile : "";
    target = others[0] ?? "";
  }

  async function submit() {
    if (mode === "saveAs" && valid) await profile({ kind: "saveAs", name: name.trim() });
    else if (mode === "rename" && valid) await profile({ kind: "rename", from: list.profile, to: name.trim() });
    else if (mode === "delete" && target) await profile({ kind: "delete", name: target });
    else return;
    mode = "idle";
  }

  function keys(e: KeyboardEvent) {
    if (e.key === "Enter") void submit();
    else if (e.key === "Escape") mode = "idle";
  }
</script>

<div class="profiles card">
  <Icon name="sliders" />
  <label for="profile-select">Profile</label>
  <select
    id="profile-select"
    value={list.profile}
    disabled={mods.busy || mode !== "idle"}
    onchange={(e) => profile({ kind: "switch", name: e.currentTarget.value })}
  >
    {#each list.profiles as p (p)}<option value={p}>{p}</option>{/each}
  </select>

  {#if mode === "saveAs" || mode === "rename"}
    <!-- svelte-ignore a11y_autofocus -->
    <input
      type="text"
      class="name"
      bind:value={name}
      maxlength="40"
      placeholder={mode === "saveAs" ? "New profile name" : "Profile name"}
      onkeydown={keys}
      autofocus
    />
    <button class="btn small primary" onclick={submit} disabled={!valid || mods.busy}>
      {mode === "saveAs" ? "Save" : "Rename"}
    </button>
    <button class="btn small ghost" onclick={() => (mode = "idle")}>Cancel</button>
    {#if clash}<span class="warn-text small">That name is taken.</span>{/if}
  {:else if mode === "delete"}
    <span class="muted small">Delete</span>
    <select bind:value={target} aria-label="Profile to delete">
      {#each others as p (p)}<option value={p}>{p}</option>{/each}
    </select>
    <button class="btn small danger" onclick={submit} disabled={!target || mods.busy}
      ><Icon name="trash" size={14} />Delete</button
    >
    <button class="btn small ghost" onclick={() => (mode = "idle")}>Cancel</button>
  {:else}
    <button
      class="btn small ghost"
      onclick={() => {
        start("saveAs");
      }}
      disabled={mods.busy}>Save as…</button
    >
    <button
      class="btn small ghost"
      onclick={() => {
        start("rename");
      }}
      disabled={mods.busy}>Rename…</button
    >
    <button
      class="btn small ghost"
      onclick={() => {
        start("delete");
      }}
      disabled={mods.busy || !others.length}
      title={others.length ? "Delete another profile" : "The active profile cannot be deleted"}>Delete…</button
    >
    <span class="faint small hint">A profile keeps an order and the enabled mods; switching applies it.</span>
  {/if}
</div>

<style>
  .profiles {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 9px 14px;
    margin-bottom: 12px;
  }

  .profiles :global(svg) {
    flex: none;
    color: var(--accent-2);
  }

  label {
    font-weight: 600;
  }

  select {
    height: 28px;
    padding: 0 8px;
    border-radius: var(--radius-sm);
    border: 1px solid var(--line-2);
    background: #101216;
    color: var(--text);
    font: inherit;
  }

  .name {
    width: 220px;
    height: 28px;
  }

  .small {
    font-size: 12.5px;
  }

  .warn-text {
    color: var(--warn);
  }

  .hint {
    margin-left: auto;
    min-width: 0;
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }
</style>
