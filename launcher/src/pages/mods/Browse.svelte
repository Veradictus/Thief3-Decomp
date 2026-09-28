<script lang="ts">
  // The mod index (Settings has its URL): search and tags, what each version
  // needs checked against the installed mods and SDK before anything is
  // downloaded, and install or update buttons. The download is checked
  // against the index's size and SHA-256 before it is installed.
  import Icon from "$components/Icon.svelte";
  import { api, type IndexMod, type IndexVersion } from "$lib/api";
  import { ago, bytes } from "$lib/format";
  import { indexTags, installButton, listText, matches, meta } from "$lib/modlist";
  import { installFromIndex, loadIndex, mods } from "$lib/mods.svelte";

  let query = $state("");
  let tag = $state<string | null>(null);
  let onlyUpdates = $state(false);
  let chosen = $state<Record<string, string>>({});

  const index = $derived(mods.index);
  const tags = $derived(indexTags(index?.mods ?? []));
  const updates = $derived(new Map((index?.updates ?? []).map((u) => [u.id, u.latest])));
  const shown = $derived(
    (index?.mods ?? []).filter((m) => matches(m, query, tag) && (!onlyUpdates || updates.has(m.id))),
  );

  function versionOf(m: IndexMod): IndexVersion | undefined {
    const wanted = chosen[m.id] ?? updates.get(m.id) ?? m.recommended;
    return m.versions.find((v) => v.version === wanted) ?? m.versions[0];
  }

  const generated = $derived(index?.generated ? ago(Date.parse(index.generated) / 1000) : "");
  const percent = (received: number, total: number) => (total ? Math.round((received * 100) / total) : 0);
</script>

<div class="toolbar">
  <div class="search">
    <Icon name="search" />
    <input type="text" placeholder="Search mods" bind:value={query} spellcheck="false" />
  </div>
  <button class="btn" onclick={() => loadIndex(true)} disabled={mods.indexLoading}>
    <Icon name="refresh" />{mods.indexLoading ? "Loading…" : "Refresh"}
  </button>
</div>

<div class="chips">
  {#if updates.size}
    <button class="chip hot" class:on={onlyUpdates} onclick={() => (onlyUpdates = !onlyUpdates)}>
      {updates.size} update{updates.size > 1 ? "s" : ""} available
    </button>
  {/if}
  <button class="chip" class:on={tag === null} onclick={() => (tag = null)}>All</button>
  {#each tags as t (t)}
    <button class="chip" class:on={tag === t} onclick={() => (tag = tag === t ? null : t)}>{t}</button>
  {/each}
</div>

{#if mods.indexError}
  <div class="note card">
    <Icon name="alert" />
    <span class="grow"
      >Could not read the mod index: {mods.indexError}. Check the connection, or the index URL in Settings.</span
    >
  </div>
{/if}

{#if index}
  <div class="entries">
    {#each shown as m (m.id)}
      {@const v = versionOf(m)}
      {@const button = installButton(m, v)}
      {@const downloading = mods.download?.id === m.id ? mods.download : null}
      <div class="entry card">
        <div class="head">
          <h3>{m.name}</h3>
          {#if m.installed}<span class="badge ok"><Icon name="check" size={12} />Installed {m.installed}</span>{/if}
          {#if updates.has(m.id)}<span class="badge info">Update: {updates.get(m.id)}</span>{/if}
          <span class="grow"></span>
          {#each m.tags as t (t)}<span class="tag">{t}</span>{/each}
        </div>
        <p class="faint small">{meta(m.authors.length > 0 && `by ${listText(m.authors)}`, m.id, m.license)}</p>
        {#if m.description}<p class="muted desc">{m.description}</p>{/if}

        {#if v}
          <div class="version">
            {#if m.versions.length > 1}
              <select
                aria-label={`Version of ${m.name}`}
                value={v.version}
                onchange={(e) => (chosen[m.id] = e.currentTarget.value)}
              >
                {#each m.versions as x (x.version)}<option value={x.version}>{x.version}</option>{/each}
              </select>
            {:else}
              <span class="mono">{v.version}</span>
            {/if}
            <span class="faint small">
              {meta(bytes(v.size), v.released && `released ${v.released}`, v.api && `T3SDK API ${v.api.toString()}`)}
            </span>
          </div>
          <ul class="notes">
            {#each v.notes as note, k (k)}
              <li class={note.severity}><Icon name="alert" size={13} />{note.message}</li>
            {:else}
              <li class="ok"><Icon name="check" size={13} />Works with your installed mods and SDK.</li>
            {/each}
          </ul>
        {/if}

        <div class="row actions">
          {#if downloading}
            <div class="progress" title="Downloading">
              <div style:width={`${percent(downloading.received, downloading.total).toString()}%`}></div>
            </div>
            <span class="faint small">{percent(downloading.received, downloading.total)}%</span>
          {:else}
            <button
              class="btn"
              class:primary={button.primary}
              disabled={!button.version || mods.busy || mods.download !== null}
              title={v && !v.compatible ? "Installs, but the problems above stay until they are fixed" : undefined}
              onclick={() => button.version && installFromIndex(m.id, button.version)}
            >
              <Icon name={m.installed ? "upload" : "download"} />{button.label}
            </button>
          {/if}
          {#if m.homepage}
            <button class="btn ghost" onclick={() => m.homepage && api.openLink(m.homepage)}>
              <Icon name="link" />Homepage
            </button>
          {/if}
        </div>
      </div>
    {:else}
      <p class="empty">
        {index.mods.length ? "No mod matches." : "The index lists no mods yet."}
      </p>
    {/each}
  </div>
  <p class="faint small source" title={index.url}>
    {meta(
      index.url,
      generated && `updated ${generated}`,
      index.skipped > 0 && `${index.skipped.toString()} entries this launcher cannot read were left out`,
    )}
  </p>
{:else if mods.indexLoading}
  <p class="empty">Reading the mod index…</p>
{/if}

<style>
  .toolbar {
    display: flex;
    gap: 8px;
    margin-bottom: 8px;
  }

  .search {
    flex: 1;
    position: relative;
    display: flex;
    align-items: center;
  }

  .search :global(svg) {
    position: absolute;
    left: 10px;
    color: var(--faint);
  }

  .search input {
    padding-left: 32px;
  }

  .chips {
    display: flex;
    flex-wrap: wrap;
    gap: 6px;
    margin-bottom: 10px;
  }

  .chip {
    height: 26px;
    padding: 0 11px;
    border-radius: 99px;
    border: 1px solid var(--line-2);
    background: var(--panel-2);
    color: var(--muted);
    cursor: pointer;
    font-size: 12.5px;
  }

  .chip:hover {
    color: var(--text);
  }

  .chip.on {
    color: var(--accent-2);
    border-color: #8d6c2c;
    background: #2a2416;
  }

  .chip.hot {
    color: var(--accent-ink);
    background: var(--accent);
    border-color: #b98d3b;
    font-weight: 600;
  }

  .chip.hot.on {
    box-shadow: 0 0 0 2px #d6ab5255;
  }

  .source {
    margin-top: 10px;
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }

  /* The results scroll here, under the search; two columns where they fit. */
  .entries {
    flex: 0 1 auto;
    min-height: 0;
    overflow: auto;
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(min(360px, 100%), 1fr));
    align-content: start;
    gap: 10px;
  }

  .entry {
    min-width: 0;
    padding: 12px 16px;
    display: grid;
    gap: 5px;
    align-content: start;
  }

  .entry > * {
    min-width: 0;
  }

  .head {
    display: flex;
    align-items: center;
    gap: 8px;
    flex-wrap: wrap;
  }

  .tag {
    font-size: 11.5px;
    color: var(--faint);
    border: 1px solid var(--line);
    border-radius: 99px;
    padding: 1px 8px;
  }

  .small {
    font-size: 12.5px;
  }

  .desc {
    display: -webkit-box;
    -webkit-line-clamp: 2;
    line-clamp: 2;
    -webkit-box-orient: vertical;
    overflow: hidden;
  }

  .version {
    display: flex;
    align-items: center;
    gap: 10px;
    margin-top: 4px;
  }

  select {
    height: 26px;
    padding: 0 6px;
    border-radius: var(--radius-sm);
    border: 1px solid var(--line-2);
    background: #101216;
    color: var(--text);
    font: inherit;
    font-size: 12.5px;
  }

  .notes {
    list-style: none;
    margin: 2px 0 0;
    padding: 0;
    display: grid;
    gap: 3px;
    font-size: 12.5px;
  }

  .notes li {
    display: flex;
    align-items: center;
    gap: 6px;
  }

  .notes .ok {
    color: var(--ok);
  }

  .notes .warning {
    color: var(--warn);
  }

  .notes .error {
    color: var(--err);
  }

  .notes .info {
    color: var(--muted);
  }

  .actions {
    margin-top: 6px;
  }

  .progress {
    width: 220px;
    height: 8px;
    border-radius: 99px;
    background: var(--panel-3);
    overflow: hidden;
  }

  .progress div {
    height: 100%;
    background: linear-gradient(90deg, var(--accent), var(--accent-2));
    transition: width 0.15s;
  }

  .note {
    display: flex;
    gap: 10px;
    align-items: flex-start;
    padding: 11px 16px;
    margin-bottom: 12px;
    color: var(--warn);
    border-color: #5b4526;
    background: #1c160d;
  }
</style>
