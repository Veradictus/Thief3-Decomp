<script lang="ts">
  // The installed packages in load order (drag the handle, or use the arrows),
  // their switches, what they hold, and the checks' issues with their fixes.
  // Loose DLLs load after them, in name order.
  import Icon from "$components/Icon.svelte";
  import Toggle from "$components/Toggle.svelte";
  import { api, type Issue, type ModPackage } from "$lib/api";
  import { app } from "$lib/app.svelte";
  import { ago, bytes } from "$lib/format";
  import { badges, dropIndex, issuesFor, listText, meta, moveBy, moveTo, worst } from "$lib/modlist";
  import {
    fix,
    mods,
    queueTextures,
    removeMod,
    setLooseEnabled,
    setOrder,
    setPackageEnabled,
    syncMods,
    textureJobs,
  } from "$lib/mods.svelte";
  import Profiles from "./Profiles.svelte";

  const list = $derived(mods.list);
  const order = $derived(list?.packages.map((p) => p.id) ?? []);
  const general = $derived(issuesFor(list, null));
  const texturesBusy = $derived(textureJobs().length > 0);

  let confirming = $state<string | null>(null);
  let drag = $state<{ id: string; from: number; to: number; y0: number; dy: number } | null>(null);
  let listElement = $state<HTMLElement>();

  function grab(e: PointerEvent, id: string, index: number) {
    if (e.button !== 0 || mods.busy) return;
    (e.currentTarget as HTMLElement).setPointerCapture(e.pointerId);
    drag = { id, from: index, to: index, y0: e.clientY, dy: 0 };
  }

  function follow(e: PointerEvent) {
    if (!drag) return;
    drag.dy = e.clientY - drag.y0;
    // The lifted row's own middle is left out by dropIndex, so its offset does not matter.
    const rows = [...(listElement?.querySelectorAll<HTMLElement>(":scope > .mod") ?? [])];
    const middles = order.map((_, i) => {
      const box = rows[i]?.getBoundingClientRect();
      return box ? box.top + box.height / 2 : Infinity;
    });
    drag.to = dropIndex(middles, e.clientY, drag.from);
  }

  function drop() {
    if (!drag) return;
    const { id, from, to } = drag;
    drag = null;
    if (to !== from) void setOrder(moveTo(order, id, to));
  }

  function nudge(e: KeyboardEvent, id: string) {
    const delta = e.key === "ArrowUp" ? -1 : e.key === "ArrowDown" ? 1 : 0;
    if (!delta) return;
    e.preventDefault();
    void setOrder(moveBy(order, id, delta));
  }

  function marker(index: number): "" | "above" | "below" {
    if (!drag || drag.to === drag.from || index !== drag.to) return "";
    return drag.to < drag.from ? "above" : "below";
  }

  const icon = (issue: Issue) => (issue.severity === "info" ? "copy" : "alert");

  function status(p: ModPackage): { label: string; kind: string } {
    if (p.error) return { label: "Broken", kind: "err" };
    if (!p.enabled) return { label: "Off", kind: "" };
    if (!p.active) return { label: "Not loaded", kind: "err" };
    return { label: "On", kind: "ok" };
  }
</script>

{#if list}
  <Profiles {list} />

  {#if !list.sdk.installed && list.packages.some((p) => p.code && p.enabled)}
    <div class="note warn card">
      <Icon name="alert" />T3SDK is not installed, so the game will not load code mods. Install it from the Play page.
    </div>
  {/if}
  {#if app.overview?.running}
    <div class="note warn card">
      <Icon name="alert" />The game is running: files it has open cannot be replaced. Close it before changing mods.
    </div>
  {/if}
  {#if mods.notice}
    <div class="note err card">
      <Icon name="alert" />
      <div class="grow">
        <strong>{mods.notice.title}</strong>
        <ul>
          {#each mods.notice.lines as line, i (i)}<li class="mono">{line}</li>{/each}
        </ul>
      </div>
      <button class="btn small ghost" onclick={() => (mods.notice = null)} aria-label="Dismiss"
        ><Icon name="x" size={14} /></button
      >
    </div>
  {/if}
  {#if list.textures.bundles.length || list.textures.needed}
    <div class="note info card">
      <Icon name="box" />
      <span class="grow">
        {#if list.textures.bundles.length}
          {list.textures.bundles.length} game bundle{list.textures.bundles.length > 1 ? "s wait" : " waits"} for the texture
          packs to be taken off first ({list.textures.bundles[0]}{list.textures.bundles.length > 1 ? ", …" : ""}).
        {:else if list.textures.mods.length}
          The texture packs changed: {listText(list.textures.mods)} go into the game's bundles as a task.
        {:else}
          No texture pack is on any more: the game's bundles go back to the originals as a task.
        {/if}
        {#if texturesBusy}<span class="faint">Queued in Tasks.</span>{/if}
      </span>
      {#if !texturesBusy}
        <button
          class="btn small"
          onclick={() => {
            queueTextures(list.textures);
          }}>Apply now</button
        >
      {/if}
    </div>
  {/if}
  {#each general as issue, i (i)}
    <div class="note card {issue.severity}"><Icon name={icon(issue)} />{issue.message}</div>
  {/each}

  <div class="card list" class:dragging={drag !== null} bind:this={listElement}>
    {#each list.packages as p, i (p.id)}
      {@const issues = issuesFor(list, p.id)}
      {@const s = status(p)}
      <div
        class="mod {marker(i)}"
        class:off={!p.enabled}
        class:lifted={drag?.id === p.id}
        style:transform={drag?.id === p.id ? `translateY(${drag.dy.toString()}px)` : undefined}
        data-id={p.id}
      >
        <button
          class="grip"
          title="Drag to change the load order (or use the arrow keys)"
          aria-label={`Move ${p.name} in the load order`}
          disabled={mods.busy}
          onpointerdown={(e) => {
            grab(e, p.id, i);
          }}
          onpointermove={follow}
          onpointerup={drop}
          onpointercancel={() => (drag = null)}
          onkeydown={(e) => {
            nudge(e, p.id);
          }}
        >
          <svg width="12" height="18" viewBox="0 0 12 18" fill="currentColor" aria-hidden="true">
            {#each [3, 9, 15] as y (y)}<circle cx="3.5" cy={y} r="1.5" /><circle cx="8.5" cy={y} r="1.5" />{/each}
          </svg>
        </button>
        <span class="pos faint mono">{i + 1}</span>
        <div class="icon" class:dim={!p.active}><Icon name={p.code ? "puzzle" : "box"} size={18} /></div>
        <div class="grow body">
          <div class="title">
            <h3>{p.name}</h3>
            {#if p.version}<span class="mono faint">{p.version}</span>{/if}
            {#each badges(p) as b (b.key)}<span class="badge kind {b.key}" title={b.title}>{b.label}</span>{/each}
            {#if worst(issues) === "error" || p.error}<span class="badge {s.kind}">{s.label}</span>{/if}
          </div>
          <p class="faint small">
            {meta(p.authors.length > 0 && `by ${listText(p.authors)}`, p.id, bytes(p.size))}
            {#if p.homepage}
              <span class="sep">·</span><button class="link" onclick={() => p.homepage && api.openLink(p.homepage)}
                >homepage</button
              >
            {/if}
          </p>
          {#if p.description}<p class="muted small desc">{p.description}</p>{/if}
          {#each issues as issue, k (k)}
            <div class="issue {issue.severity}">
              <Icon name={icon(issue)} size={14} />
              <span class="grow">{issue.message}</span>
              {#if issue.fix}
                {@const action = issue.fix.action}
                <button class="btn small" disabled={mods.busy} onclick={() => fix(action)}>{issue.fix.label}</button>
              {/if}
            </div>
          {/each}
        </div>
        <div class="actions">
          <button
            class="btn small ghost arrow up"
            aria-label={`Load ${p.name} earlier`}
            title="Load earlier"
            disabled={mods.busy || i === 0}
            onclick={() => setOrder(moveBy(order, p.id, -1))}><Icon name="chevron" size={14} /></button
          >
          <button
            class="btn small ghost arrow down"
            aria-label={`Load ${p.name} later`}
            title="Load later"
            disabled={mods.busy || i === list.packages.length - 1}
            onclick={() => setOrder(moveBy(order, p.id, 1))}><Icon name="chevron" size={14} /></button
          >
          <Toggle
            checked={p.enabled}
            label={`Enable ${p.name}`}
            disabled={mods.busy || !!p.error}
            onchange={(on) => setPackageEnabled(p.id, on)}
          />
          {#if confirming === p.id}
            <span class="confirm small">Remove?</span>
            <button
              class="btn small danger"
              disabled={mods.busy}
              onclick={() => {
                confirming = null;
                void removeMod(p.id);
              }}>Remove</button
            >
            <button class="btn small ghost" onclick={() => (confirming = null)}>Keep</button>
          {:else}
            <button
              class="btn small ghost danger"
              aria-label={`Remove ${p.name}`}
              title="Remove"
              disabled={mods.busy}
              onclick={() => (confirming = p.id)}><Icon name="trash" size={14} /></button
            >
          {/if}
        </div>
      </div>
    {:else}
      <div class="empty">
        <h3>No mod packages yet</h3>
        <p>
          Install a <code>.t3mod</code> with <em>Install mod…</em>, drop one onto this window, or pick one in Browse.
        </p>
        <p class="row center">
          <button
            class="btn small"
            onclick={() => api.openLink("https://github.com/Veradictus/Thief3-Decomp/blob/main/docs/mods.md")}
          >
            <Icon name="book" size={14} />The mod package format
          </button>
        </p>
      </div>
    {/each}
  </div>

  {#if list.loose.length}
    <h2 class="section">Loose DLLs</h2>
    <p class="muted small section-note">
      DLLs put straight into <code>System\mods</code>. They load after the packages, in name order; switching one off
      moves it to <code>System\mods\disabled</code>.
    </p>
    <div class="card list">
      {#each list.loose as m (m.name)}
        <div class="mod" class:off={!m.enabled}>
          <div class="icon" class:dim={!m.enabled}><Icon name="puzzle" size={18} /></div>
          <div class="grow body">
            <div class="title">
              <h3>{m.name}</h3>
              <span class="badge kind loose">Loose DLL</span>
            </div>
            <p class="faint small">
              <span class="mono">{m.name}.dll</span> · {bytes(m.size)} · changed {ago(m.modified)}
            </p>
          </div>
          <div class="actions">
            <Toggle
              checked={m.enabled}
              label={`Enable ${m.name}`}
              disabled={mods.busy}
              onchange={(on) => setLooseEnabled(m.name, on)}
            />
          </div>
        </div>
      {/each}
    </div>
  {/if}

  <div class="row foot">
    <span class="faint small mono">{list.dir}</span>
    <span class="grow"></span>
    {#if list.textures.mods.length}
      <button
        class="btn small ghost"
        disabled={texturesBusy}
        onclick={() => {
          queueTextures(list.textures, true);
        }}
      >
        <Icon name="box" size={14} />Apply texture packs again
      </button>
    {/if}
    <button
      class="btn small ghost"
      disabled={mods.busy}
      title="Write the load order and put every mod's files in place again"
      onclick={syncMods}><Icon name="refresh" size={14} />Apply again</button
    >
  </div>
{:else}
  <p class="empty">{app.config?.gameDir ? "Reading the mods folder…" : "Set the game folder in Settings first."}</p>
{/if}

<style>
  .list {
    overflow: hidden;
  }

  .list.dragging {
    user-select: none;
  }

  .mod {
    position: relative;
    display: flex;
    align-items: flex-start;
    gap: 12px;
    padding: 13px 16px 13px 8px;
    border-top: 1px solid var(--line);
    background: var(--panel);
  }

  .mod:first-child {
    border-top: 0;
  }

  .mod.lifted {
    z-index: 2;
    box-shadow: 0 10px 28px #000a;
    border-radius: var(--radius-sm);
    background: var(--panel-2);
  }

  .mod.above::before,
  .mod.below::after {
    content: "";
    position: absolute;
    left: 10px;
    right: 10px;
    height: 2px;
    background: var(--accent);
    border-radius: 2px;
  }

  .mod.above::before {
    top: -1px;
  }

  .mod.below::after {
    bottom: -1px;
  }

  .mod.off .body {
    opacity: 0.62;
  }

  .grip {
    align-self: center;
    display: grid;
    place-items: center;
    width: 22px;
    height: 34px;
    border: 0;
    border-radius: 5px;
    background: none;
    color: var(--faint);
    cursor: grab;
    touch-action: none;
  }

  .grip:hover:not(:disabled),
  .grip:focus-visible {
    color: var(--text);
    background: var(--panel-3);
  }

  .lifted .grip {
    cursor: grabbing;
  }

  .pos {
    align-self: center;
    width: 18px;
    text-align: right;
  }

  .icon {
    flex: none;
    width: 38px;
    height: 38px;
    border-radius: 9px;
    display: grid;
    place-items: center;
    background: #2a2416;
    color: var(--accent-2);
  }

  .icon.dim {
    background: var(--panel-3);
    color: var(--faint);
  }

  .title {
    display: flex;
    align-items: center;
    flex-wrap: wrap;
    gap: 8px;
  }

  .small {
    font-size: 12.5px;
    margin-top: 2px;
  }

  .desc {
    margin-top: 4px;
    max-width: 80ch;
  }

  .badge.kind {
    height: 19px;
    font-size: 11px;
    letter-spacing: 0.02em;
  }

  .badge.code {
    color: #c9a2ef;
    border-color: #4a3560;
    background: #1d1626;
  }

  .badge.content {
    color: var(--info);
    border-color: #2f4560;
    background: #121b26;
  }

  .badge.textures {
    color: #86c2b4;
    border-color: #2d5249;
    background: #13211d;
  }

  .issue {
    display: flex;
    align-items: center;
    gap: 8px;
    margin-top: 7px;
    padding: 5px 8px 5px 10px;
    border-radius: var(--radius-sm);
    font-size: 12.5px;
    border: 1px solid var(--line-2);
  }

  .issue.error {
    color: var(--err);
    border-color: #5c2e26;
    background: #26140f;
  }

  .issue.warning {
    color: var(--warn);
    border-color: #5b4526;
    background: #241b10;
  }

  .issue.info {
    color: var(--muted);
  }

  .actions {
    display: flex;
    align-items: center;
    gap: 6px;
    align-self: center;
  }

  .arrow {
    width: 28px;
    padding: 0;
    justify-content: center;
  }

  .arrow.up :global(svg) {
    transform: rotate(-90deg);
  }

  .arrow.down :global(svg) {
    transform: rotate(90deg);
  }

  .sep {
    margin: 0 3px 0 1px;
  }

  .confirm {
    color: #f4a595;
    margin: 0 2px;
  }

  .link {
    padding: 0;
    border: 0;
    background: none;
    color: var(--accent-2);
    text-decoration: underline;
    cursor: pointer;
    font-size: inherit;
  }

  .note {
    display: flex;
    gap: 10px;
    align-items: flex-start;
    padding: 11px 16px;
    margin-bottom: 12px;
  }

  .note :global(svg) {
    flex: none;
    margin-top: 2px;
  }

  .note.warn,
  .note.warning {
    color: var(--warn);
    border-color: #5b4526;
    background: #1c160d;
  }

  .note.err,
  .note.error {
    color: var(--err);
    border-color: #5c2e26;
    background: #1f120f;
  }

  .note.info {
    color: var(--info);
    border-color: #2f4560;
    background: #111821;
    align-items: center;
  }

  .note ul {
    margin: 6px 0 0;
    padding-left: 18px;
    color: var(--muted);
  }

  .section {
    margin: 26px 0 4px;
    font-size: 17px;
  }

  .section-note {
    margin-bottom: 10px;
  }

  .center {
    justify-content: center;
    margin-top: 12px;
  }

  .foot {
    margin-top: 14px;
  }
</style>
