<script lang="ts">
  import { onMount } from "svelte";
  import DropOverlay from "$components/DropOverlay.svelte";
  import Icon from "$components/Icon.svelte";
  import UpdateBanner from "$components/UpdateBanner.svelte";
  import { api, inTauri } from "$lib/api";
  import { app, jobs, loadConfig, pending, refresh, running, type Page } from "$lib/app.svelte";
  import { startupUpdateCheck } from "$lib/update.svelte";
  import Maps from "./pages/Maps.svelte";
  import Mods from "./pages/Mods.svelte";
  import Play from "./pages/Play.svelte";
  import Saves from "./pages/Saves.svelte";
  import Sdk from "./pages/Sdk.svelte";
  import Settings from "./pages/Settings.svelte";
  import Tasks from "./pages/Tasks.svelte";

  const nav: { page: Page; label: string; icon: string }[] = [
    { page: "play", label: "Play", icon: "play" },
    { page: "maps", label: "Map Studio", icon: "map" },
    { page: "mods", label: "Mods", icon: "puzzle" },
    { page: "saves", label: "Saves", icon: "archive" },
    { page: "sdk", label: "SDK settings", icon: "sliders" },
    { page: "tasks", label: "Tasks", icon: "terminal" },
  ];

  onMount(() => {
    const start = new URLSearchParams(location.search).get("page") as Page | null;
    if (start) app.page = start;
    void loadConfig().then(refresh).then(startupUpdateCheck);
    // Pick up changes made outside the launcher (the game, Godot, a shell).
    const onFocus = () => void refresh();
    const timer = setInterval(() => {
      if (document.visibilityState === "visible") void refresh();
    }, 15000);
    window.addEventListener("focus", onFocus);
    return () => {
      clearInterval(timer);
      window.removeEventListener("focus", onFocus);
    };
  });

  const current = $derived(running());
  const lastLine = $derived(current?.lines.at(-1)?.line ?? "");
  const game = $derived(app.overview?.game ?? null);
</script>

{#if !app.config}
  <div class="loading"></div>
{:else if !app.config.setupComplete}
  <main class="setup"><Settings setup /></main>
{:else}
  <div class="shell">
    <aside>
      <div class="brand">
        <img src="/icon.svg" alt="" width="34" height="34" />
        <div>
          <div class="name">T3SDK</div>
          <div class="faint tag">Launcher</div>
        </div>
      </div>
      <nav>
        {#each nav as item (item.page)}
          <button class:active={app.page === item.page} onclick={() => (app.page = item.page)}>
            <Icon name={item.icon} size={17} />
            <span class="grow">{item.label}</span>
            {#if item.page === "tasks" && pending()}<span class="count">{pending()}</span>{/if}
          </button>
        {/each}
      </nav>
      <div class="grow"></div>
      <UpdateBanner />
      <!-- The running job lives here, not over the page, so it never hides content. -->
      {#if current}
        <button
          class="job"
          title="Show its output in Tasks"
          onclick={() => {
            jobs.selected = current.key;
            app.page = "tasks";
          }}
        >
          <span class="row">
            <span class="spinner"></span>
            <strong class="grow clip">{current.title}</strong>
            {#if pending() > 1}
              <span class="faint queued" title={`${pending() - 1} more queued`}>+{pending() - 1}</span>
            {/if}
          </span>
          <span class="mono faint clip">{lastLine || "Starting…"}</span>
        </button>
      {/if}
      <div class="status">
        {#if game}
          <span class="badge" class:ok={game.supported} class:warn={!game.supported}>
            <span class="dot"></span>{game.supported ? "Game supported" : "Unsupported build"}
          </span>
        {:else}
          <span class="badge err"><span class="dot"></span>No game folder</span>
        {/if}
        {#if !inTauri}<span class="badge info">Browser preview</span>{/if}
      </div>
      <nav>
        <button class="link" onclick={() => api.openLink("https://discord.gg/hdAXH73tEG")}>
          <Icon name="discord" size={16} /><span class="grow">Taffer Tavern</span>
        </button>
        <button class="link" onclick={() => api.openLink("https://veradictus.github.io/Thief3-Decomp/")}>
          <Icon name="book" size={16} /><span class="grow">Documentation</span>
        </button>
        <button class:active={app.page === "settings"} onclick={() => (app.page = "settings")}>
          <Icon name="gear" size={17} /><span class="grow">Settings</span>
        </button>
      </nav>
    </aside>

    <main>
      {#if app.page === "play"}<Play />
      {:else if app.page === "maps"}<Maps />
      {:else if app.page === "mods"}<Mods />
      {:else if app.page === "saves"}<Saves />
      {:else if app.page === "sdk"}<Sdk />
      {:else if app.page === "tasks"}<Tasks />
      {:else}<Settings />{/if}
    </main>
  </div>
{/if}

<DropOverlay />

<div class="toasts">
  {#each app.toasts as t (t.id)}
    <div class="toast" class:error={t.kind === "error"}>
      <Icon name={t.kind === "error" ? "alert" : "check"} />{t.text}
    </div>
  {/each}
</div>

<style>
  .shell {
    display: grid;
    grid-template-columns: 224px 1fr;
    height: 100%;
  }

  aside {
    display: flex;
    flex-direction: column;
    gap: 6px;
    padding: 18px 12px 14px;
    background: #111215;
    border-right: 1px solid var(--line);
  }

  .brand {
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 0 8px 18px;
  }

  .name {
    font-family: var(--serif);
    font-size: 19px;
    font-weight: 600;
    letter-spacing: 0.04em;
    line-height: 1.1;
  }

  .tag {
    font-size: 11.5px;
    letter-spacing: 0.16em;
    text-transform: uppercase;
  }

  nav {
    display: flex;
    flex-direction: column;
    gap: 2px;
  }

  nav button {
    display: flex;
    align-items: center;
    gap: 11px;
    height: 38px;
    padding: 0 12px;
    border: 0;
    border-radius: 8px;
    background: none;
    color: var(--muted);
    cursor: pointer;
    text-align: left;
  }

  nav button:hover {
    background: var(--panel-2);
    color: var(--text);
  }

  nav button.active {
    background: var(--panel-3);
    color: var(--text);
    box-shadow: inset 3px 0 0 var(--accent);
  }

  nav button.active :global(svg) {
    color: var(--accent-2);
  }

  nav button.link {
    height: 32px;
    font-size: 13px;
  }

  .count {
    min-width: 20px;
    height: 20px;
    padding: 0 6px;
    border-radius: 99px;
    background: var(--accent);
    color: var(--accent-ink);
    font-size: 11.5px;
    font-weight: 700;
    display: grid;
    place-items: center;
  }

  .status {
    display: flex;
    flex-direction: column;
    align-items: flex-start;
    gap: 6px;
    padding: 0 8px 10px;
  }

  main {
    min-width: 0;
    height: 100%;
    overflow: hidden;
  }

  .setup {
    max-width: 980px;
    margin: 0 auto;
  }

  .job {
    display: grid;
    gap: 2px;
    margin-bottom: 4px;
    padding: 8px 12px;
    border-radius: 8px;
    border: 1px solid var(--line-2);
    background: var(--panel-2);
    cursor: pointer;
    text-align: left;
  }

  .job:hover {
    background: var(--panel-3);
    border-color: #474d57;
  }

  .job .mono {
    font-size: 12px;
  }

  .clip {
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }

  .queued {
    font-size: 12px;
  }

  .spinner {
    width: 14px;
    height: 14px;
    border-radius: 50%;
    border: 2px solid #d6ab5240;
    border-top-color: var(--accent);
    animation: spin 0.8s linear infinite;
    flex: none;
  }

  @keyframes spin {
    to {
      transform: rotate(360deg);
    }
  }

  /* Bottom right: the page's buttons are at the top right. */
  .toasts {
    position: fixed;
    right: 20px;
    bottom: 16px;
    display: flex;
    flex-direction: column;
    gap: 8px;
    z-index: 10;
    max-width: 420px;
  }

  .toast {
    display: flex;
    gap: 9px;
    align-items: flex-start;
    padding: 10px 14px;
    border-radius: var(--radius-sm);
    background: #1d2024;
    border: 1px solid var(--line-2);
    box-shadow: 0 8px 24px #0009;
    color: var(--text);
  }

  .toast :global(svg) {
    color: var(--ok);
    margin-top: 2px;
  }

  .toast.error {
    border-color: #6b3228;
    background: #231512;
  }

  .toast.error :global(svg) {
    color: var(--err);
  }
</style>
