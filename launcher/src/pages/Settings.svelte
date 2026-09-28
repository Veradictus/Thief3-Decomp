<script lang="ts">
  // Paths to the game, Godot, Python and the T3SDK tools. Also the first-run
  // setup screen (`setup`), prefilled from detection.
  import { onMount } from "svelte";
  import Icon from "$components/Icon.svelte";
  import PathField from "$components/PathField.svelte";
  import { api, emptyConfig, launcherVersion, type Config, type Detected } from "$lib/api";
  import { mods } from "$lib/mods.svelte";
  import { app, guard, saveConfig, toast } from "$lib/app.svelte";

  let { setup = false }: { setup?: boolean } = $props();

  let draft = $state<Config>({ ...(app.config ?? emptyConfig) });
  let detected = $state<Detected | null>(null);
  let detecting = $state(false);
  let gameOk = $state(false);
  let godotOk = $state(false);
  let pythonOk = $state(false);
  let rootOk = $state(false);
  let version = $state("");

  const ready = $derived(gameOk && pythonOk && rootOk);
  const dirty = $derived(JSON.stringify(draft) !== JSON.stringify(app.config));

  async function detect() {
    detecting = true;
    detected = (await guard(api.detectAll())) ?? null;
    detecting = false;
    if (!detected) return;
    // Fill empty fields with the first candidate; never overwrite a choice.
    draft.gameDir ??= detected.games[0]?.path ?? null;
    draft.godot ??= detected.godots[0]?.path ?? null;
    draft.sdkRoot ??= detected.sdkRoots[0]?.path ?? null;
    draft.python ??= detected.pythons[0]?.path ?? null;
  }

  onMount(() => {
    if (setup || !app.config?.gameDir) void detect();
    void launcherVersion().then((v) => (version = v));
  });

  const DEFAULT_INDEX = "https://veradictus.github.io/Thief3-Decomp/modindex/index.json";
  const indexUrlOk = $derived(!draft.modIndexUrl || /^https:\/\/[^\s/?#]+/.test(draft.modIndexUrl));

  async function save() {
    if (draft.modIndexUrl !== app.config?.modIndexUrl) mods.index = null; // the Mods page reads the new index
    await guard(saveConfig({ ...draft, setupComplete: true }));
    if (setup) app.page = "play";
    else toast("Settings saved.");
  }

  const gameCheck = async (path: string) => {
    const r = await api.checkGame(path);
    return { ok: r.ok, message: r.message, detail: r.steam ? "Steam install" : undefined };
  };
  const godotCheck = async (path: string) => {
    const r = await api.checkGodot(path);
    return { ok: r.ok, message: r.message, detail: r.version ? `Godot ${r.version}` : undefined };
  };
  const pythonCheck = async (path: string) => {
    const r = await api.checkPython(path);
    return { ok: r.ok, message: r.message, detail: r.version ? `Python ${r.version}` : undefined };
  };
  const rootCheck = async (path: string) => {
    const r = await api.checkSdkRoot(path);
    return { ok: r.ok, message: r.message, detail: r.sdkBuilt ? "SDK built" : "SDK not built yet" };
  };
  const projectCheck = (path: string) => Promise.resolve({ ok: true, message: `Maps are exported to ${path}.` });
</script>

<div class="page">
  {#if setup}
    <div class="welcome">
      <img src="/icon.svg" alt="" width="64" height="64" />
      <div>
        <h1>Welcome, taffer.</h1>
        <p class="muted">
          Tell the launcher where things are. It found what it could; check each entry and fix the ones marked.
          Everything stays on this computer.
        </p>
      </div>
    </div>
  {:else}
    <div class="page-head">
      <div>
        <h1>Settings</h1>
        <p>Where the game and the tools are. Stored in your user profile, not in the game folder.</p>
      </div>
    </div>
  {/if}

  <div class="fields">
    <PathField
      label="Thief: Deadly Shadows"
      bind:value={draft.gameDir}
      bind:ok={gameOk}
      hint="The game folder: it contains System and Content. The Steam release (patch 1.1) gets the full SDK."
      candidates={detected?.games}
      check={gameCheck}
      action={{ label: "Get Thief: Deadly Shadows on Steam", href: "https://store.steampowered.com/app/6980/" }}
    />
    <PathField
      label="T3SDK folder"
      bind:value={draft.sdkRoot}
      bind:ok={rootOk}
      hint="The T3SDK tools and SDK. The launcher ships with its own copy; a T3SDK checkout (for developers) works too."
      candidates={detected?.sdkRoots}
      check={rootCheck}
      action={{ label: "Get T3SDK", href: "https://github.com/Veradictus/Thief3-Decomp" }}
    />
    <PathField
      label="Python"
      bind:value={draft.python}
      bind:ok={pythonOk}
      directory={false}
      hint="Runs the T3SDK tools (SDK install, map export, repack). The launcher ships with one; any Python 3.10+ works too."
      candidates={detected?.pythons}
      check={pythonCheck}
      action={{ label: "Get Python", href: "https://www.python.org/downloads/" }}
    />
    <PathField
      label="Godot"
      bind:value={draft.godot}
      bind:ok={godotOk}
      directory={false}
      optional
      hint="Godot 4.7 or newer, to view and edit exported maps. Not needed to play."
      candidates={detected?.godots}
      check={godotCheck}
      action={{ label: "Get Godot", href: "https://godotengine.org/download/" }}
    />
    {#if !setup}
      <PathField
        label="Godot project folder"
        bind:value={draft.projectDir}
        optional
        hint="Where maps are exported. Empty: build\assets\godot in the T3SDK folder."
        check={projectCheck}
      />
      <div class="field card">
        <div class="row">
          <div class="grow">
            <h3>Mod index</h3>
            <p class="muted hint">
              The list of published mods that the Mods page browses and checks for updates. Empty: the T3SDK index.
            </p>
          </div>
          {#if !indexUrlOk}<span class="badge err"><Icon name="alert" size={13} />Not an https:// URL</span>{/if}
        </div>
        <div class="row">
          <input
            type="text"
            spellcheck="false"
            placeholder={DEFAULT_INDEX}
            value={draft.modIndexUrl ?? ""}
            oninput={(e) => (draft.modIndexUrl = e.currentTarget.value.trim() || null)}
          />
          <button class="btn" onclick={() => (draft.modIndexUrl = null)} disabled={!draft.modIndexUrl}>Default</button>
        </div>
      </div>
    {/if}
  </div>

  <div class="actions">
    <button class="btn ghost" onclick={detect} disabled={detecting}>
      <Icon name="search" />{detecting ? "Searching…" : "Search again"}
    </button>
    <div class="grow"></div>
    {#if setup}
      <button class="btn ghost" onclick={() => saveConfig({ ...draft, setupComplete: true })}>Skip for now</button>
      <button class="btn primary" onclick={save} disabled={!ready}>Continue<Icon name="chevron" /></button>
    {:else}
      <button class="btn" onclick={() => (draft = { ...(app.config ?? emptyConfig) })} disabled={!dirty}>Revert</button>
      <button class="btn primary" onclick={save} disabled={!dirty || !indexUrlOk}><Icon name="check" />Save</button>
    {/if}
  </div>

  {#if !setup}
    <div class="about card">
      <h3>About</h3>
      <p class="muted">
        T3SDK Launcher {version}. T3SDK is a fan project, not affiliated with or endorsed by the owners of the Thief
        series. It changes the game only in memory while it runs; map repacks and content mods replace game files only
        while they are installed or enabled, after backing up the originals.
      </p>
      <div class="row">
        <button class="btn small" onclick={() => saveConfig({ ...(app.config ?? emptyConfig), setupComplete: false })}
          >Run setup again</button
        >
      </div>
    </div>
  {/if}
</div>

<style>
  .welcome {
    display: flex;
    gap: 18px;
    align-items: center;
    margin: 6px 0 24px;
  }

  .welcome p {
    margin-top: 6px;
    max-width: 70ch;
  }

  .fields {
    display: grid;
    gap: 12px;
    max-width: 900px;
  }

  .field {
    padding: 16px 18px;
    display: flex;
    flex-direction: column;
    gap: 10px;
  }

  .hint {
    margin-top: 2px;
    font-size: 13px;
  }

  .actions {
    display: flex;
    gap: 8px;
    align-items: center;
    max-width: 900px;
    margin-top: 18px;
  }

  .about {
    max-width: 900px;
    margin-top: 28px;
    padding: 16px 18px;
    display: grid;
    gap: 10px;
  }
</style>
