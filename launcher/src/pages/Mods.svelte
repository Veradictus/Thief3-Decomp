<script lang="ts">
  // The mod manager: installed packages in load order, with profiles and
  // checks (mods/Installed.svelte), and the mod index (mods/Browse.svelte).
  // Every change is saved and applied to the game folder at once.
  import Icon from "$components/Icon.svelte";
  import { api, pickModPackages } from "$lib/api";
  import { app, guard } from "$lib/app.svelte";
  import { installFiles, loadIndex, loadMods, mods } from "$lib/mods.svelte";
  import Browse from "./mods/Browse.svelte";
  import Installed from "./mods/Installed.svelte";

  let tab = $state<"installed" | "browse">("installed");

  $effect(() => {
    void app.revision;
    void loadMods();
  });

  // Fetched once per session, for the updates count; Refresh in Browse fetches again.
  $effect(() => {
    if (!mods.index && !mods.indexLoading && !mods.indexError) void loadIndex(false);
  });

  const updates = $derived(mods.index?.updates.length ?? 0);
  const installed = $derived((mods.list?.packages.length ?? 0) + (mods.list?.loose.length ?? 0));

  async function install() {
    await installFiles(await pickModPackages());
  }
</script>

<div class="page">
  <div class="page-head">
    <h1>Mods</h1>
    <div class="row">
      <button class="btn primary" onclick={install} disabled={mods.busy}><Icon name="download" />Install mod…</button>
      <button class="btn" onclick={() => guard(api.openLocation("mods"))}><Icon name="folder" />Open folder</button>
    </div>
    <p>
      Changes apply at once: the load order and the game's files follow every switch, and code mods load when the game
      next starts. Drop <code>.t3mod</code> files onto the window to install them.
    </p>
  </div>

  <div class="tabs" role="tablist">
    <button
      role="tab"
      aria-selected={tab === "installed"}
      class:active={tab === "installed"}
      onclick={() => (tab = "installed")}
    >
      <Icon name="puzzle" size={15} />Installed<span class="count">{installed}</span>
    </button>
    <button
      role="tab"
      aria-selected={tab === "browse"}
      class:active={tab === "browse"}
      onclick={() => (tab = "browse")}
    >
      <Icon name="search" size={15} />Browse
      {#if updates}<span class="count hot" title="Installed mods with a newer compatible version"
          >{updates} update{updates > 1 ? "s" : ""}</span
        >{/if}
    </button>
  </div>

  {#if tab === "installed"}
    <Installed />
  {:else}
    <Browse />
  {/if}
</div>

<style>
  .tabs {
    display: flex;
    gap: 4px;
    margin-bottom: 12px;
    border-bottom: 1px solid var(--line);
  }

  .tabs button {
    display: inline-flex;
    align-items: center;
    gap: 8px;
    height: 34px;
    padding: 0 12px;
    border: 0;
    border-bottom: 2px solid transparent;
    background: none;
    color: var(--muted);
    cursor: pointer;
    margin-bottom: -1px;
  }

  .tabs button:hover {
    color: var(--text);
  }

  .tabs button.active {
    color: var(--text);
    border-bottom-color: var(--accent);
  }

  .count {
    min-width: 20px;
    height: 19px;
    padding: 0 7px;
    border-radius: 99px;
    background: var(--panel-3);
    color: var(--muted);
    font-size: 11.5px;
    display: inline-grid;
    place-items: center;
  }

  .count.hot {
    background: var(--accent);
    color: var(--accent-ink);
    font-weight: 700;
  }
</style>
