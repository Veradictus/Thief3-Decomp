<script lang="ts">
  // Map Studio: export a map to Godot, edit it there, repack it into a .gmp and
  // install it into the game (and put the original back).
  import Icon from "$components/Icon.svelte";
  import { api, type MapEntry } from "$lib/api";
  import { app, enqueue, guard, running } from "$lib/app.svelte";
  import { ago, bytes } from "$lib/format";

  let maps = $state<MapEntry[]>([]);
  let filter = $state("");
  let selectedId = $state<string | null>(null);

  $effect(() => {
    void app.revision;
    void load();
  });

  async function load() {
    maps = (await guard(api.listMaps())) ?? maps;
    if (!selectedId || !maps.some((m) => m.id === selectedId)) selectedId = maps[0]?.id ?? null;
  }

  const shown = $derived(
    maps.filter((m) => `${m.title ?? ""} ${m.id}`.toLowerCase().includes(filter.trim().toLowerCase())),
  );
  const sel = $derived(maps.find((m) => m.id === selectedId) ?? null);
  const hasGodot = $derived(!!app.config?.godot);
  const busy = $derived(running() !== null);

  function exportMap(level: string | null) {
    const job = enqueue({ kind: "export", level }, `Export ${level ?? "all maps"}`);
    if (hasGodot) enqueue({ kind: "import" }, "Import into Godot", job);
  }

  // Nodes added in Godot that are not T3 actors, which the edits file cannot
  // save ("2 nodes"), or "" when there are none.
  function notSaved(m: MapEntry): string {
    return m.notSaved ? `${m.notSaved} node${m.notSaved > 1 ? "s" : ""}` : "";
  }

  function stage(m: MapEntry): { label: string; kind: "" | "ok" | "warn" | "info" } {
    if (m.installed) return { label: "Installed", kind: "ok" };
    if (m.stale) return { label: "Repack needed", kind: "warn" };
    if (m.patched) return { label: "Repacked", kind: "info" };
    if (m.editedActors) return { label: `${m.editedActors} edited`, kind: "warn" };
    if (m.exported) return { label: "Exported", kind: "" };
    return { label: "", kind: "" };
  }
</script>

<div class="page">
  <div class="page-head">
    <h1>Map Studio</h1>
    <div class="row">
      <button class="btn" onclick={() => guard(api.openGodot(null, true))} disabled={!hasGodot}>
        <Icon name="edit" />Open project in Godot
      </button>
      <button
        class="btn"
        onclick={() => {
          exportMap(null);
        }}
        disabled={busy}><Icon name="download" />Export all</button
      >
    </div>
    <p>
      Export a map to Godot, move things around, then repack it and try it in the game. Originals are backed up before
      anything is replaced.
    </p>
  </div>

  <div class="split">
    <div class="list card">
      <div class="search">
        <Icon name="search" />
        <input type="text" placeholder="Filter maps" bind:value={filter} spellcheck="false" />
      </div>
      <div class="rows">
        {#each shown as m (m.id)}
          {@const s = stage(m)}
          <button class="map" class:active={m.id === selectedId} onclick={() => (selectedId = m.id)}>
            <div class="grow names">
              <span class="name" title={m.title ?? m.id}>{m.title ?? m.id}</span>
              <span class="faint mono">{m.id}.gmp</span>
            </div>
            {#if s.label}<span class="badge {s.kind}">{s.label}</span>{/if}
          </button>
        {:else}
          <p class="empty">{maps.length ? "No map matches." : "No maps found: check the game folder in Settings."}</p>
        {/each}
      </div>
    </div>

    <div class="detail card">
      {#if sel}
        <div class="detail-head">
          <div class="grow">
            <h2 class="clip" title={sel.title ?? sel.id}>{sel.title ?? sel.id}</h2>
            <p class="muted">
              <span class="mono">{sel.id}.gmp</span>
              {#if sel.size}
                · {bytes(sel.size)}{/if}
              {#if sel.actors}
                · {sel.actors} actors{/if}
            </p>
          </div>
          <button
            class="btn small ghost"
            title="Rewrite the unchanged map and compare it byte for byte"
            onclick={() => enqueue({ kind: "roundtrip", level: sel.id }, `Round-trip check: ${sel.id}`)}
            disabled={busy || !sel.inGame}
          >
            <Icon name="check" size={14} />Round-trip check
          </button>
        </div>

        <!-- Each step: its name and buttons on one line, what it does below. -->
        <div class="stage" class:done={sel.exported}>
          <div class="num">1</div>
          <h3>Export to Godot</h3>
          <div class="row actions">
            <button
              class="btn"
              class:primary={!sel.exported}
              onclick={() => {
                exportMap(sel.id);
              }}
              disabled={busy || !sel.inGame}
            >
              <Icon name="download" />{sel.exported ? "Re-export" : "Export"}
            </button>
          </div>
          <p class="muted">
            {sel.exported ? "Exported: scene, meshes, textures, lights and every actor's data." : "Not exported yet."}
          </p>
        </div>

        <div class="stage" class:done={!!sel.editedActors}>
          <div class="num">2</div>
          <h3>Edit</h3>
          <div class="row actions">
            <button
              class="btn"
              class:primary={sel.exported && !sel.editedActors}
              onclick={() => guard(api.openGodot(sel.id, true))}
              disabled={!sel.exported || !hasGodot}><Icon name="edit" />Edit in Godot</button
            >
            <button
              class="btn"
              onclick={() => guard(api.openGodot(sel.id, false))}
              disabled={!sel.exported || !hasGodot}
            >
              <Icon name="eye" />View
            </button>
          </div>
          <p class="muted">
            {#if sel.editedActors}
              {sel.editedActors} actor{sel.editedActors > 1 ? "s" : ""} changed · saved {ago(sel.editsTime)}
              {#if notSaved(sel)}<span class="warn-text"> · {notSaved(sel)} not saved</span>{/if}
            {:else}
              Move, rotate, scale, duplicate (Ctrl+D) or delete actors, or change their properties, then save (Ctrl+S).
            {/if}
          </p>
        </div>

        <div class="stage" class:done={sel.patched && !sel.stale}>
          <div class="num">3</div>
          <h3>Repack</h3>
          <div class="row actions">
            <button
              class="btn"
              class:primary={!!sel.editedActors && (!sel.patched || sel.stale)}
              onclick={() => enqueue({ kind: "repack", level: sel.id }, `Repack ${sel.id}`)}
              disabled={busy || !sel.editedActors}
            >
              <Icon name="box" />Repack
            </button>
          </div>
          <p class="muted">
            {#if sel.stale}
              <span class="warn-text">The edits changed after the last repack.</span>
            {:else if sel.patched}
              Patched map built {ago(sel.patchedTime)}.
            {:else if sel.exported && sel.editedActors === null}
              Nothing to repack yet: no edits saved in Godot.
            {:else if sel.editedActors === 0 && notSaved(sel)}
              <span class="warn-text">Nothing to repack: {notSaved(sel)} added in Godot are not T3 actors.</span> A new actor
              is a copy of one in the map: select it and press Ctrl+D.
            {:else if sel.editedActors === 0}
              Nothing to repack: the saved edits change no actors.
            {:else}
              Writes a patched copy of the map; the game folder is not touched.
            {/if}
          </p>
        </div>

        <div class="stage" class:done={sel.installed}>
          <div class="num">4</div>
          <h3>Install</h3>
          <div class="row actions">
            {#if sel.installed}
              <button
                class="btn danger"
                onclick={() => enqueue({ kind: "restore", level: sel.id }, `Restore ${sel.id}`)}
                disabled={busy}
              >
                <Icon name="undo" />Restore original
              </button>
            {/if}
            <button
              class="btn"
              class:primary={sel.patched && !sel.installed && !sel.stale}
              onclick={() => enqueue({ kind: "install", level: sel.id }, `Install ${sel.id}`)}
              disabled={busy || !sel.patched}
            >
              <Icon name="upload" />{sel.installed ? "Reinstall" : "Install"}
            </button>
          </div>
          <p class="muted">
            {#if sel.installed}
              The game uses the patched map. The original is backed up.
            {:else}
              Copies the patched map into the game, after backing up the original once.
            {/if}
          </p>
        </div>

        <div class="row foot">
          <button class="btn small ghost" onclick={() => guard(api.openLocation("project"))}
            ><Icon name="folder" size={14} />Godot project</button
          >
          <button class="btn small ghost" onclick={() => guard(api.openLocation("patched"))}
            ><Icon name="folder" size={14} />Patched maps</button
          >
          <button class="btn small ghost" onclick={() => guard(api.openLocation("backup"))}
            ><Icon name="folder" size={14} />Backups</button
          >
          <div class="grow"></div>
          <button
            class="btn small ghost danger"
            onclick={() => enqueue({ kind: "restore", level: null }, "Restore all maps")}
            disabled={busy}
          >
            <Icon name="undo" size={14} />Restore all originals
          </button>
        </div>
      {:else}
        <p class="empty">Pick a map.</p>
      {/if}
    </div>
  </div>
</div>

<style>
  /* The rest of the page: the list scrolls inside its card, the steps fit beside it. */
  .split {
    flex: 1 1 0;
    min-height: 280px;
    display: grid;
    grid-template-columns: clamp(230px, 32%, 320px) minmax(0, 1fr);
    grid-template-rows: minmax(0, 1fr);
    gap: 12px;
  }

  .list {
    display: flex;
    flex-direction: column;
    min-height: 0;
    overflow: hidden;
  }

  .search {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 10px 12px;
    border-bottom: 1px solid var(--line);
    color: var(--faint);
  }

  .search:focus-within {
    border-bottom-color: var(--accent);
    color: var(--accent-2);
  }

  .search input {
    border: 0;
    background: transparent;
    height: 26px;
    padding: 0;
    box-shadow: none !important;
  }

  .rows {
    flex: 1;
    min-height: 0;
    overflow: auto;
    padding: 6px;
  }

  .map {
    width: 100%;
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 7px 10px;
    border: 1px solid transparent;
    border-radius: var(--radius-sm);
    background: none;
    text-align: left;
    cursor: pointer;
  }

  .map:hover {
    background: var(--panel-2);
  }

  .map.active {
    background: var(--panel-3);
    border-color: var(--line-2);
  }

  .names {
    display: flex;
    flex-direction: column;
  }

  .name {
    font-weight: 600;
  }

  .names span,
  .clip {
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }

  .names .mono {
    font-size: 11.5px;
  }

  .detail {
    display: flex;
    flex-direction: column;
    min-height: 0;
    overflow: auto;
    padding: 16px 18px;
  }

  .detail-head {
    display: flex;
    gap: 12px;
    align-items: flex-start;
    margin-bottom: 10px;
  }

  .detail-head p {
    margin-top: 2px;
  }

  .stage {
    display: grid;
    grid-template-columns: 30px minmax(0, 1fr) auto;
    grid-template-areas:
      "num title actions"
      "num text text";
    column-gap: 12px;
    align-items: center;
    padding: 10px 0;
    border-top: 1px solid var(--line);
  }

  .stage h3 {
    grid-area: title;
  }

  .actions {
    grid-area: actions;
  }

  .stage p {
    grid-area: text;
    margin-top: 2px;
    font-size: 13px;
  }

  .num {
    grid-area: num;
    align-self: start;
    margin-top: 1px;
    width: 30px;
    height: 30px;
    border-radius: 50%;
    display: grid;
    place-items: center;
    border: 1px solid var(--line-2);
    color: var(--muted);
    font-family: var(--serif);
  }

  .stage.done .num {
    background: #1c2a1e;
    border-color: #3d6343;
    color: var(--ok);
  }

  .warn-text {
    color: var(--warn);
  }

  .foot {
    margin-top: auto;
    border-top: 1px solid var(--line);
    padding-top: 10px;
    flex-wrap: wrap;
    row-gap: 4px;
  }
</style>
