<script lang="ts">
  // Mod DLLs in System/mods. Turning one off moves it to System/mods/disabled,
  // which the SDK does not load.
  import Icon from "$components/Icon.svelte";
  import Toggle from "$components/Toggle.svelte";
  import { api, type ModEntry } from "$lib/api";
  import { app, guard, refresh } from "$lib/app.svelte";
  import { ago, bytes } from "$lib/format";

  let mods = $state<ModEntry[]>([]);

  $effect(() => {
    void app.revision;
    void load();
  });

  async function load() {
    mods = (await guard(api.listMods())) ?? mods;
  }

  async function set(mod: ModEntry, enabled: boolean) {
    if ((await guard(api.setModEnabled(mod.name, enabled))) === undefined) mod.enabled = !enabled;
    await refresh();
  }
</script>

<div class="page">
  <div class="page-head">
    <h1>Mods</h1>
    <div class="row">
      <button class="btn" onclick={load}><Icon name="refresh" />Refresh</button>
      <button class="btn" onclick={() => guard(api.openLocation("mods"))}><Icon name="folder" />Open folder</button>
    </div>
    <p>
      T3SDK loads every DLL in <code>System\mods</code> when the game starts, in name order. Changes apply on the next start.
    </p>
  </div>

  {#if !app.overview?.sdk.installed}
    <div class="note card">
      <Icon name="alert" />T3SDK is not installed, so the game will not load these mods. Install it from the Play page.
    </div>
  {/if}

  <!-- Name order, left to right: the order the SDK loads them in. -->
  <div class="list card">
    {#each mods as mod (mod.name)}
      <div class="mod">
        <div class="icon" class:off={!mod.enabled}><Icon name="puzzle" size={17} /></div>
        <div class="grow">
          <h3 title={`${mod.name}.dll`}>{mod.name}</h3>
          <p class="faint small">{bytes(mod.size)} · changed {ago(mod.modified)}</p>
        </div>
        <Toggle checked={mod.enabled} label={`Enable ${mod.name}`} onchange={(on) => set(mod, on)} />
      </div>
    {:else}
      <div class="empty">
        <h3>No mods yet</h3>
        <p>Put a mod's DLL into <code>System\mods</code>, or build one from the SDK's example.</p>
        <p class="row center">
          <button
            class="btn small"
            onclick={() =>
              api.openLink("https://github.com/Veradictus/Thief3-Decomp/blob/main/docs/sdk.md#writing-a-mod")}
          >
            <Icon name="book" size={14} />Writing a mod
          </button>
        </p>
      </div>
    {/each}
  </div>
</div>

<style>
  /* As tall as its mods, and no taller than the window: then it scrolls. Two
     columns where they fit. */
  .list {
    flex: 0 1 auto;
    min-height: 0;
    overflow: auto;
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(320px, 1fr));
    align-content: start;
  }

  /* Rules above and to the left of each mod; the card clips those of the
     first row and column. */
  .mod {
    display: flex;
    align-items: center;
    gap: 12px;
    min-width: 0;
    padding: 10px 16px;
    box-shadow:
      0 -1px 0 var(--line),
      -1px 0 0 var(--line);
  }

  .mod h3,
  .mod p {
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }

  .empty {
    grid-column: 1 / -1;
  }

  .icon {
    width: 34px;
    height: 34px;
    flex: none;
    border-radius: 8px;
    display: grid;
    place-items: center;
    background: #2a2416;
    color: var(--accent-2);
  }

  .icon.off {
    background: var(--panel-3);
    color: var(--faint);
  }

  .small {
    font-size: 12.5px;
    margin-top: 2px;
  }

  .note {
    display: flex;
    gap: 10px;
    align-items: center;
    padding: 12px 16px;
    margin-bottom: 12px;
    color: var(--warn);
    border-color: #5b4526;
    background: #1c160d;
  }

  .center {
    justify-content: center;
    margin-top: 12px;
  }
</style>
