<script lang="ts">
  // The installed packages in load order, left to right (drag a mod onto
  // another's place, or use the arrows), their switches, what they hold, and
  // the checks' issues with their fixes. Loose DLLs load after them, in name
  // order. The list scrolls inside its own panel.
  import Icon from "$components/Icon.svelte";
  import Toggle from "$components/Toggle.svelte";
  import { api, type Issue, type ModPackage } from "$lib/api";
  import { app } from "$lib/app.svelte";
  import { ago, bytes } from "$lib/format";
  import { badges, dropIndex, issuesFor, listText, meta, moveBy, moveTo } from "$lib/modlist";
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
  let drag = $state<{ id: string; from: number; to: number; x0: number; y0: number; dx: number; dy: number } | null>(
    null,
  );
  let panel = $state<HTMLElement>();

  function grab(e: PointerEvent, id: string, index: number) {
    if (e.button !== 0 || mods.busy) return;
    (e.currentTarget as HTMLElement).setPointerCapture(e.pointerId);
    drag = { id, from: index, to: index, x0: e.clientX, y0: e.clientY, dx: 0, dy: 0 };
  }

  function follow(e: PointerEvent) {
    if (!drag) return;
    const d = drag;
    d.dx = e.clientX - d.x0;
    d.dy = e.clientY - d.y0;
    // Cells where they sit in the grid; the lifted one is only drawn moved.
    const cells = [...(panel?.querySelectorAll<HTMLElement>(":scope > .mod.package") ?? [])];
    const centres = cells.map((cell, i) => {
      const box = cell.getBoundingClientRect();
      const lifted = i === d.from;
      return {
        x: box.left + box.width / 2 - (lifted ? d.dx : 0),
        y: box.top + box.height / 2 - (lifted ? d.dy : 0),
      };
    });
    d.to = dropIndex(centres, { x: e.clientX, y: e.clientY }, d.from);
  }

  function drop() {
    if (!drag) return;
    const { id, from, to } = drag;
    drag = null;
    if (to !== from) void setOrder(moveTo(order, id, to));
  }

  function nudge(e: KeyboardEvent, id: string) {
    const back = e.key === "ArrowUp" || e.key === "ArrowLeft";
    const forward = e.key === "ArrowDown" || e.key === "ArrowRight";
    if (!back && !forward) return;
    e.preventDefault();
    void setOrder(moveBy(order, id, back ? -1 : 1));
  }

  const icon = (issue: Issue) => (issue.severity === "info" ? "copy" : "alert");

  function tooltip(p: ModPackage): string {
    return [p.name, p.description, p.homepage].filter(Boolean).join("\n");
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
      <div class="grow notice">
        <strong>{mods.notice.title}:</strong>
        {#each mods.notice.lines as line, i (i)}<span class="mono">{line}</span>{/each}
      </div>
      <button class="btn small ghost" onclick={() => (mods.notice = null)} aria-label="Dismiss">
        <Icon name="x" size={14} />
      </button>
    </div>
  {/if}
  {#if list.textures.bundles.length || list.textures.needed}
    <div class="note info card">
      <Icon name="box" />
      <span class="grow">
        {#if list.textures.bundles.length}
          {list.textures.bundles.length} game bundle{list.textures.bundles.length > 1 ? "s wait" : " waits"} for the texture
          packs to come off first ({list.textures.bundles[0]}{list.textures.bundles.length > 1 ? ", …" : ""}).
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

  <!-- Load order, left to right and top to bottom; loose DLLs after the packages. -->
  <div class="list card" class:dragging={drag !== null} bind:this={panel}>
    {#each list.packages as p, i (p.id)}
      {@const issues = issuesFor(list, p.id)}
      <div
        class="mod package"
        class:off={!p.enabled}
        class:lifted={drag?.id === p.id}
        class:target={drag !== null && drag.to !== drag.from && drag.to === i}
        style:transform={drag?.id === p.id ? `translate(${drag.dx.toString()}px, ${drag.dy.toString()}px)` : undefined}
      >
        <div class="main">
          <button
            class="grip"
            title="Drag onto another mod's place to change the load order (or use the arrow keys)"
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
            <svg width="10" height="16" viewBox="0 0 10 16" fill="currentColor" aria-hidden="true">
              {#each [3, 8, 13] as y (y)}<circle cx="2.5" cy={y} r="1.4" /><circle cx="7.5" cy={y} r="1.4" />{/each}
            </svg>
          </button>
          <div class="icon" class:dim={!p.active} title={`Load order: ${(i + 1).toString()}`}>{i + 1}</div>
          <div class="grow body">
            <div class="title" title={tooltip(p)}>
              <h3>{p.name}</h3>
              {#if p.version}<span class="mono faint version">{p.version}</span>{/if}
            </div>
            <p class="faint small">
              {#each badges(p) as b (b.key)}<span class="kind {b.key}" title={b.title}>{b.label}</span>{/each}
              {meta(p.authors.length > 0 && listText(p.authors), bytes(p.size))}
            </p>
          </div>
          {#if confirming === p.id}
            <div class="actions">
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
            </div>
          {:else}
            <div class="actions">
              <button
                class="btn small ghost arrow up"
                aria-label={`Load ${p.name} earlier`}
                title="Load earlier"
                disabled={mods.busy || i === 0}
                onclick={() => setOrder(moveBy(order, p.id, -1))}><Icon name="chevron" size={13} /></button
              >
              <button
                class="btn small ghost arrow down"
                aria-label={`Load ${p.name} later`}
                title="Load later"
                disabled={mods.busy || i === list.packages.length - 1}
                onclick={() => setOrder(moveBy(order, p.id, 1))}><Icon name="chevron" size={13} /></button
              >
              <Toggle
                checked={p.enabled}
                label={`Enable ${p.name}`}
                disabled={mods.busy || !!p.error}
                onchange={(on) => setPackageEnabled(p.id, on)}
              />
              <button
                class="btn small ghost danger arrow"
                aria-label={`Remove ${p.name}`}
                title="Remove"
                disabled={mods.busy}
                onclick={() => (confirming = p.id)}><Icon name="trash" size={13} /></button
              >
            </div>
          {/if}
        </div>
        {#each issues as issue, k (k)}
          <div class="issue {issue.severity}">
            <Icon name={icon(issue)} size={13} />
            <span class="grow">{issue.message}</span>
            {#if issue.fix}
              {@const action = issue.fix.action}
              <button class="btn small" disabled={mods.busy} onclick={() => fix(action)}>{issue.fix.label}</button>
            {/if}
          </div>
        {/each}
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
            onclick={() => api.openLink("https://github.com/Veradictus/Thief3-Decomp/blob/master/docs/mods.md")}
          >
            <Icon name="book" size={14} />The mod package format
          </button>
        </p>
      </div>
    {/each}

    {#if list.loose.length}
      <div class="group faint small">
        <strong>Loose DLLs</strong> · straight in <code>System\mods</code>; they load after the packages, in name order,
        and switching one off moves it to <code>System\mods\disabled</code>.
      </div>
      {#each list.loose as m (m.name)}
        <div class="mod" class:off={!m.enabled}>
          <div class="main">
            <span class="grip-space"></span>
            <div class="icon" class:dim={!m.enabled}><Icon name="puzzle" size={16} /></div>
            <div class="grow body">
              <div class="title" title={`${m.name}.dll`}><h3>{m.name}</h3></div>
              <p class="faint small">
                <span class="kind loose">Loose DLL</span>{meta(
                  bytes(m.size),
                  m.modified && `changed ${ago(m.modified)}`,
                )}
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
        </div>
      {/each}
    {/if}
  </div>

  <div class="row foot">
    <span class="faint small mono path" title={list.dir}>{list.dir}</span>
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
  /* As tall as its mods, and no taller than the window: then it scrolls.
     Two columns where they fit. */
  .list {
    flex: 0 1 auto;
    min-height: 0;
    overflow: auto;
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(min(360px, 100%), 1fr));
    align-content: start;
  }

  .list.dragging {
    user-select: none;
  }

  /* Rules above and to the left of each mod; the card clips those of the
     first row and column. */
  .mod {
    position: relative;
    min-width: 0;
    padding: 10px 14px 10px 6px;
    box-shadow:
      0 -1px 0 var(--line),
      -1px 0 0 var(--line);
    background: var(--panel);
  }

  .mod.lifted {
    z-index: 2;
    background: var(--panel-2);
    border-radius: var(--radius-sm);
    box-shadow: 0 10px 28px #000a;
  }

  .mod.target {
    box-shadow: inset 0 0 0 2px var(--accent);
  }

  .main {
    display: flex;
    align-items: center;
    gap: 10px;
    min-width: 0;
  }

  .mod.off .body {
    opacity: 0.62;
  }

  .grip,
  .grip-space {
    flex: none;
    width: 16px;
  }

  .grip {
    display: grid;
    place-items: center;
    height: 30px;
    padding: 0;
    border: 0;
    border-radius: 4px;
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

  .icon {
    flex: none;
    width: 34px;
    height: 34px;
    border-radius: 8px;
    display: grid;
    place-items: center;
    background: #2a2416;
    color: var(--accent-2);
    font-family: var(--serif);
    font-size: 15px;
    font-weight: 600;
  }

  .icon.dim {
    background: var(--panel-3);
    color: var(--faint);
  }

  .title {
    display: flex;
    align-items: baseline;
    gap: 7px;
    min-width: 0;
  }

  .title h3,
  .body p {
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }

  .version {
    flex: none;
    font-size: 11.5px;
  }

  .small {
    font-size: 12.5px;
  }

  .body p {
    margin-top: 1px;
  }

  .kind {
    display: inline-block;
    margin-right: 6px;
    padding: 0 6px;
    border-radius: 99px;
    border: 1px solid var(--line-2);
    font-size: 11px;
    line-height: 16px;
    vertical-align: 1px;
  }

  .kind.code {
    color: #c9a2ef;
    border-color: #4a3560;
    background: #1d1626;
  }

  .kind.content {
    color: var(--info);
    border-color: #2f4560;
    background: #121b26;
  }

  .kind.textures {
    color: #86c2b4;
    border-color: #2d5249;
    background: #13211d;
  }

  .kind.loose {
    color: var(--muted);
  }

  .actions {
    flex: none;
    display: flex;
    align-items: center;
    gap: 2px;
  }

  .actions :global(.toggle) {
    margin: 0 4px;
  }

  .arrow {
    width: 26px;
    padding: 0;
    justify-content: center;
  }

  .arrow.up :global(svg) {
    transform: rotate(-90deg);
  }

  .arrow.down :global(svg) {
    transform: rotate(90deg);
  }

  .confirm {
    color: #f4a595;
    margin-right: 4px;
  }

  .issue {
    display: flex;
    align-items: center;
    gap: 7px;
    margin: 6px 0 0 26px;
    padding: 3px 4px 3px 8px;
    border-radius: var(--radius-sm);
    font-size: 12px;
    line-height: 1.35;
    border: 1px solid var(--line-2);
  }

  .issue :global(svg) {
    flex: none;
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

  .group {
    grid-column: 1 / -1;
    padding: 12px 16px 8px;
    box-shadow: 0 -1px 0 var(--line);
  }

  .group strong {
    color: var(--text);
  }

  .note {
    display: flex;
    gap: 10px;
    align-items: center;
    padding: 8px 14px;
    margin-bottom: 10px;
  }

  .note :global(svg) {
    flex: none;
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
  }

  .notice {
    display: flex;
    flex-wrap: wrap;
    gap: 2px 10px;
    max-height: 64px;
    overflow: auto;
  }

  .notice .mono {
    color: var(--muted);
  }

  .empty {
    grid-column: 1 / -1;
  }

  .center {
    justify-content: center;
    margin-top: 12px;
  }

  .foot {
    margin-top: 10px;
  }

  .path {
    flex: 1;
    min-width: 0;
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }
</style>
