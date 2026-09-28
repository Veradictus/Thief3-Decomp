<script lang="ts">
  // Home: start the game, and the state of the SDK, mods and maps at a glance.
  import Icon from "$components/Icon.svelte";
  import { api } from "$lib/api";
  import { app, enqueue, guard, refresh, running, toast } from "$lib/app.svelte";

  let log = $state<string[]>([]);
  let logView = $state<HTMLPreElement>();
  let follow = $state(true);
  let launching = $state(false);

  const o = $derived(app.overview);
  const game = $derived(o?.game ?? null);
  const busy = $derived(running() !== null);

  async function loadLog() {
    log = (await guard(api.readSdkLog(200))) ?? [];
  }

  $effect(() => {
    void app.revision;
    if (app.config?.gameDir) void loadLog();
  });

  // The log panel takes the height that is left; keep its newest lines in view,
  // unless the reader has scrolled up (the log reloads with every refresh).
  $effect(() => {
    void log;
    if (follow && logView) logView.scrollTop = logView.scrollHeight;
  });

  function onLogScroll() {
    if (logView) follow = logView.scrollTop + logView.clientHeight >= logView.scrollHeight - 8;
  }

  async function play() {
    launching = true;
    const message = await guard(api.launchGame());
    if (message) toast(message);
    setTimeout(() => {
      launching = false;
      void refresh();
    }, 4000);
  }

  function sdkTitle() {
    if (!o) return "";
    if (o.sdk.installed) return o.sdk.managed ? "Installed" : "Installed manually";
    return o.sdk.built ? "Not installed" : "Not built";
  }
</script>

<div class="page">
  <section class="hero card">
    <div class="hero-text">
      <p class="eyebrow">Ion Storm · 2004</p>
      <h1 class="title">Thief: Deadly Shadows</h1>
      <p class="sub">
        {#if !game}
          Set the game folder in Settings to play.
        {:else if game.supported}
          Steam release, patch 1.1 · {game.maps} maps · T3SDK {o?.sdk.installed ? "active" : "not installed"}
        {:else}
          Unsupported T3Main.exe: the game runs without T3SDK. Map tools still work.
        {/if}
      </p>
    </div>
    <div class="hero-play">
      <div class="glow"></div>
      <button class="btn primary play" onclick={play} disabled={!game?.ok || launching || o?.running}>
        <Icon name="play" size={18} />{o?.running ? "Running" : launching ? "Starting…" : "Play"}
      </button>
      {#if game?.steam}<span class="faint small">Starts through Steam, like its Play button.</span>{/if}
    </div>
  </section>

  <div class="tiles">
    <div class="tile card">
      <div class="tile-head">
        <Icon name="shield" />
        <h3>Game</h3>
      </div>
      {#if game}
        <span class="badge" class:ok={game.supported} class:warn={!game.supported}>
          <span class="dot"></span>{game.supported ? "Supported build" : "Unsupported build"}
        </span>
        <p class="muted small">{game.steam ? "Steam install" : "Not a Steam install"}</p>
      {:else}
        <span class="badge err"><span class="dot"></span>Not set</span>
      {/if}
      <div class="row tile-actions">
        <button class="btn small" onclick={() => guard(api.openLocation("game"))} disabled={!game}
          ><Icon name="folder" size={14} />Folder</button
        >
      </div>
    </div>

    <div class="tile card">
      <div class="tile-head">
        <Icon name="box" />
        <h3>T3SDK</h3>
      </div>
      <span class="badge" class:ok={o?.sdk.installed} class:warn={o && !o.sdk.installed}>
        <span class="dot"></span>{sdkTitle()}
      </span>
      <p class="muted small">Fixes, widescreen, borderless window, and the mod loader.</p>
      <div class="row tile-actions">
        {#if o?.sdk.installed}
          <button
            class="btn small danger"
            disabled={busy || !o.sdk.managed}
            onclick={() => enqueue({ kind: "sdkUndeploy" }, "Remove T3SDK")}>Remove</button
          >
        {:else}
          <button
            class="btn small"
            disabled={busy || !o?.sdk.built}
            onclick={() => enqueue({ kind: "sdkDeploy" }, "Install T3SDK")}
            ><Icon name="download" size={14} />Install</button
          >
        {/if}
        {#if o?.sdk.buildable}
          <button
            class="btn small ghost"
            disabled={busy}
            title="Needs Visual Studio with the C++ tools"
            onclick={() => enqueue({ kind: "sdkBuild" }, "Build T3SDK")}><Icon name="hammer" size={14} />Build</button
          >
        {/if}
      </div>
    </div>

    <div class="tile card">
      <div class="tile-head">
        <Icon name="puzzle" />
        <h3>Mods</h3>
      </div>
      <p class="big">
        {o?.modsEnabled ?? 0}<span class="muted small"> enabled{o?.modsDisabled ? `, ${o.modsDisabled} off` : ""}</span>
      </p>
      <div class="row tile-actions">
        <button class="btn small" onclick={() => (app.page = "mods")}>Manage</button>
      </div>
    </div>

    <div class="tile card">
      <div class="tile-head">
        <Icon name="map" />
        <h3>Maps</h3>
      </div>
      <p class="big">{o?.maps.exported ?? 0}<span class="muted small"> of {o?.maps.total ?? 0} exported</span></p>
      <p class="muted small">
        {o?.maps.installed
          ? `${o.maps.installed} modified map${o.maps.installed > 1 ? "s" : ""} installed`
          : "All maps original"}
      </p>
      <div class="row tile-actions">
        <button class="btn small" onclick={() => (app.page = "maps")}>Map Studio</button>
      </div>
    </div>
  </div>

  <section class="log card">
    <div class="row log-head">
      <h3 class="grow">T3SDK.log</h3>
      <button class="btn small ghost" onclick={loadLog}><Icon name="refresh" size={14} />Refresh</button>
      <button class="btn small ghost" onclick={() => guard(api.openLocation("log"))}
        ><Icon name="folder" size={14} />Open</button
      >
    </div>
    {#if log.length}
      <pre bind:this={logView} onscroll={onLogScroll}>{log.join("\n")}</pre>
    {:else}
      <p class="empty small">No log yet: it appears after the first run with T3SDK installed.</p>
    {/if}
  </section>
</div>

<style>
  /* Title on the left, Play on the right in the light: one short band instead of
     a tall banner, so the tiles and the log fit under it. */
  .hero {
    position: relative;
    overflow: hidden;
    display: flex;
    align-items: center;
    gap: 24px;
    padding: 22px 28px;
    background:
      radial-gradient(120% 140% at 85% 0%, #3b2e17 0%, transparent 55%),
      radial-gradient(80% 120% at 10% 120%, #13202a 0%, transparent 60%), linear-gradient(180deg, #16181c, #101114);
  }

  .hero-text {
    flex: 1;
    min-width: 0;
  }

  .hero-play {
    position: relative;
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 8px;
    max-width: 210px;
    text-align: center;
  }

  .glow {
    position: absolute;
    left: 50%;
    top: 50%;
    width: 220px;
    height: 220px;
    transform: translate(-50%, -50%);
    border-radius: 50%;
    background: radial-gradient(circle, #f6c86a55 0%, #d6ab5222 35%, transparent 70%);
    filter: blur(2px);
    pointer-events: none;
  }

  .eyebrow {
    color: var(--accent);
    letter-spacing: 0.18em;
    text-transform: uppercase;
    font-size: 11.5px;
  }

  .title {
    font-size: 34px;
    line-height: 1.2;
    margin-top: 2px;
    text-shadow: 0 2px 18px #000a;
  }

  .sub {
    color: var(--muted);
    margin-top: 4px;
  }

  .play {
    position: relative;
    height: 46px;
    padding: 0 30px;
    font-size: 16px;
    letter-spacing: 0.04em;
    box-shadow: 0 6px 24px #d6ab5230;
  }

  .hero-play .small {
    position: relative;
    text-wrap: balance;
  }

  .small {
    font-size: 12.5px;
  }

  .tiles {
    display: grid;
    grid-template-columns: repeat(4, minmax(0, 1fr));
    gap: 12px;
    margin-top: 12px;
  }

  .tile {
    padding: 12px 14px;
    display: flex;
    flex-direction: column;
    gap: 6px;
    align-items: flex-start;
  }

  .tile-head {
    display: flex;
    align-items: center;
    gap: 8px;
    color: var(--accent-2);
  }

  .tile-head h3 {
    color: var(--text);
  }

  .tile-actions {
    margin-top: auto;
    padding-top: 4px;
    flex-wrap: wrap;
  }

  .big {
    font-family: var(--serif);
    font-size: 26px;
    line-height: 1.1;
  }

  .big span {
    font-family: var(--sans);
    margin-left: 4px;
  }

  /* Whatever height is left; the log scrolls inside. */
  .log {
    flex: 1 1 0;
    min-height: 150px;
    display: flex;
    flex-direction: column;
    margin-top: 12px;
    padding: 10px 14px 14px;
  }

  .log-head {
    margin-bottom: 8px;
  }

  pre {
    flex: 1;
    min-height: 0;
    margin: 0;
    padding: 10px 12px;
    background: #0b0c0e;
    border: 1px solid var(--line);
    border-radius: var(--radius-sm);
    font: 12px/1.55 var(--mono);
    color: #c9c4b8;
    overflow: auto;
    white-space: pre-wrap;
    overflow-wrap: anywhere;
  }
</style>
