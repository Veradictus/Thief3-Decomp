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
    <div>
      <h1>Mods</h1>
      <p>
        T3SDK loads every DLL in <code>System\mods</code> when the game starts, in name order. Changes apply on the next start.
      </p>
    </div>
    <div class="row">
      <button class="btn" onclick={load}><Icon name="refresh" />Refresh</button>
      <button class="btn" onclick={() => guard(api.openLocation("mods"))}><Icon name="folder" />Open folder</button>
    </div>
  </div>

  {#if !app.overview?.sdk.installed}
    <div class="note card">
      <Icon name="alert" />T3SDK is not installed, so the game will not load these mods. Install it from the Play page.
    </div>
  {/if}

  <div class="card">
    {#each mods as mod (mod.name)}
      <div class="mod">
        <div class="icon" class:off={!mod.enabled}><Icon name="puzzle" size={18} /></div>
        <div class="grow">
          <h3>{mod.name}</h3>
          <p class="faint small">
            <span class="mono">{mod.name}.dll</span> · {bytes(mod.size)} · changed {ago(mod.modified)}
          </p>
        </div>
        <span class="badge" class:ok={mod.enabled}>{mod.enabled ? "Enabled" : "Off"}</span>
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
  .mod {
    display: flex;
    align-items: center;
    gap: 14px;
    padding: 14px 18px;
    border-top: 1px solid var(--line);
  }

  .mod:first-child {
    border-top: 0;
  }

  .icon {
    width: 38px;
    height: 38px;
    border-radius: 9px;
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
