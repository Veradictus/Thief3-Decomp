<script lang="ts">
  // Map Studio: export a map to Godot, edit it there, repack it into a .gmp and
  // install it into the game (and put the original back).
  import Icon from "../components/Icon.svelte";
  import { api, type MapEntry } from "../lib/api";
  import { ago, app, bytes, enqueue, guard, running } from "../lib/app.svelte";

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
    <div>
      <h1>Map Studio</h1>
      <p>Export a map to Godot, move things around, then repack it and try it in the game. Originals are backed up before anything is replaced.</p>
    </div>
    <div class="row">
      <button class="btn" onclick={() => guard(api.openGodot(null, true))} disabled={!hasGodot}>
        <Icon name="edit" />Open project in Godot
      </button>
      <button class="btn" onclick={() => exportMap(null)} disabled={busy}><Icon name="download" />Export all</button>
    </div>
  </div>

  <ol class="steps">
    <li><span>1</span>Export<em>map → Godot scene</em></li>
    <li><span>2</span>Edit<em>Godot, then "Save T3 edits"</em></li>
    <li><span>3</span>Repack<em>edits → patched .gmp</em></li>
    <li><span>4</span>Install<em>into the game, original kept</em></li>
  </ol>

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
              <span class="name">{m.title ?? m.id}</span>
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
            <h2>{sel.title ?? sel.id}</h2>
            <p class="muted">
              <span class="mono">{sel.id}.gmp</span>
              {#if sel.size} · {bytes(sel.size)}{/if}
              {#if sel.actors} · {sel.actors} actors{/if}
            </p>
          </div>
          <button class="btn small ghost" title="Rewrite the unchanged map and compare it byte for byte"
            onclick={() => enqueue({ kind: "roundtrip", level: sel.id }, `Round-trip check: ${sel.id}`)} disabled={busy || !sel.inGame}>
            <Icon name="check" size={14} />Round-trip check
          </button>
        </div>

        <div class="stage" class:done={sel.exported}>
          <div class="num">1</div>
          <div class="grow">
            <h3>Export to Godot</h3>
            <p class="muted">{sel.exported ? "Exported: scene, meshes, textures, lights and every actor's data." : "Not exported yet."}</p>
          </div>
          <button class="btn" class:primary={!sel.exported} onclick={() => exportMap(sel.id)} disabled={busy || !sel.inGame}>
            <Icon name="download" />{sel.exported ? "Re-export" : "Export"}
          </button>
        </div>

        <div class="stage" class:done={!!sel.editedActors}>
          <div class="num">2</div>
          <div class="grow">
            <h3>Edit</h3>
            <p class="muted">
              {#if sel.editedActors}
                {sel.editedActors} actor{sel.editedActors > 1 ? "s" : ""} changed · saved {ago(sel.editsTime)}
              {:else}
                Move, rotate and scale actors, or change their properties, then use <em>Save T3 edits</em>.
              {/if}
            </p>
          </div>
          <div class="row">
            <button class="btn" class:primary={sel.exported && !sel.editedActors} onclick={() => guard(api.openGodot(sel.id, true))}
              disabled={!sel.exported || !hasGodot}><Icon name="edit" />Edit in Godot</button>
            <button class="btn" onclick={() => guard(api.openGodot(sel.id, false))} disabled={!sel.exported || !hasGodot}>
              <Icon name="eye" />View
            </button>
          </div>
        </div>

        <div class="stage" class:done={sel.patched && !sel.stale}>
          <div class="num">3</div>
          <div class="grow">
            <h3>Repack</h3>
            <p class="muted">
              {#if sel.stale}
                <span class="warn-text">The edits changed after the last repack.</span>
              {:else if sel.patched}
                Patched map built {ago(sel.patchedTime)}.
              {:else}
                Writes a patched copy of the map; the game folder is not touched.
              {/if}
            </p>
          </div>
          <button class="btn" class:primary={!!sel.editedActors && (!sel.patched || sel.stale)}
            onclick={() => enqueue({ kind: "repack", level: sel.id }, `Repack ${sel.id}`)} disabled={busy || !sel.editedActors}>
            <Icon name="box" />Repack
          </button>
        </div>

        <div class="stage" class:done={sel.installed}>
          <div class="num">4</div>
          <div class="grow">
            <h3>Install</h3>
            <p class="muted">
              {#if sel.installed}
                The game uses the patched map. The original is backed up.
              {:else}
                Copies the patched map into the game, after backing up the original once.
              {/if}
            </p>
          </div>
          <div class="row">
            {#if sel.installed}
              <button class="btn danger" onclick={() => enqueue({ kind: "restore", level: sel.id }, `Restore ${sel.id}`)} disabled={busy}>
                <Icon name="undo" />Restore original
              </button>
            {/if}
            <button class="btn" class:primary={sel.patched && !sel.installed && !sel.stale}
              onclick={() => enqueue({ kind: "install", level: sel.id }, `Install ${sel.id}`)} disabled={busy || !sel.patched}>
              <Icon name="upload" />{sel.installed ? "Reinstall" : "Install"}
            </button>
          </div>
        </div>

        <div class="row foot">
          <button class="btn small ghost" onclick={() => guard(api.openLocation("project"))}><Icon name="folder" size={14} />Godot project</button>
          <button class="btn small ghost" onclick={() => guard(api.openLocation("patched"))}><Icon name="folder" size={14} />Patched maps</button>
          <button class="btn small ghost" onclick={() => guard(api.openLocation("backup"))}><Icon name="folder" size={14} />Backups</button>
          <div class="grow"></div>
          <button class="btn small ghost danger" onclick={() => enqueue({ kind: "restore", level: null }, "Restore all maps")} disabled={busy}>
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
  .steps {
    list-style: none;
    display: grid;
    grid-template-columns: repeat(4, 1fr);
    gap: 10px;
    padding: 0;
    margin: 0 0 16px;
  }

  .steps li {
    display: grid;
    grid-template-columns: auto 1fr;
    column-gap: 10px;
    align-items: center;
    padding: 10px 14px;
    border: 1px dashed var(--line-2);
    border-radius: var(--radius);
    font-weight: 600;
  }

  .steps span {
    grid-row: span 2;
    width: 26px;
    height: 26px;
    border-radius: 50%;
    display: grid;
    place-items: center;
    background: #2a2416;
    color: var(--accent-2);
    font-family: var(--serif);
  }

  .steps em {
    font-style: normal;
    font-weight: 400;
    color: var(--muted);
    font-size: 12.5px;
  }

  .split {
    display: grid;
    grid-template-columns: minmax(260px, 340px) 1fr;
    gap: 12px;
    align-items: start;
  }

  .list {
    overflow: hidden;
    position: sticky;
    top: 0;
  }

  .search {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 10px 12px;
    border-bottom: 1px solid var(--line);
    color: var(--faint);
  }

  .search input {
    border: 0;
    background: transparent;
    height: 26px;
    padding: 0;
    box-shadow: none !important;
  }

  .rows {
    max-height: calc(100vh - 330px);
    overflow: auto;
    padding: 6px;
  }

  .map {
    width: 100%;
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 8px 10px;
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

  .names .mono {
    font-size: 11.5px;
  }

  .detail {
    padding: 18px 20px;
  }

  .detail-head {
    display: flex;
    gap: 12px;
    align-items: flex-start;
    margin-bottom: 14px;
  }

  .detail-head p {
    margin-top: 3px;
  }

  .stage {
    display: flex;
    align-items: center;
    gap: 14px;
    padding: 14px 0;
    border-top: 1px solid var(--line);
  }

  .stage p {
    margin-top: 2px;
    font-size: 13px;
  }

  .num {
    width: 30px;
    height: 30px;
    flex: none;
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
    border-top: 1px solid var(--line);
    padding-top: 12px;
    flex-wrap: wrap;
  }
</style>
