<script lang="ts">
  // T3SDK.ini as switches. The list, order and descriptions come from the
  // SDK's own T3SDK.ini, so new settings show up without launcher changes.
  import Icon from "../components/Icon.svelte";
  import Toggle from "../components/Toggle.svelte";
  import { api, type SdkSettings, type Setting } from "../lib/api";
  import { app, guard, refresh, toast } from "../lib/app.svelte";

  let settings = $state<SdkSettings | null>(null);
  let values = $state<Record<string, string>>({});
  let saved = $state<Record<string, string>>({});

  const id = (section: string, key: string) => `${section}.${key}`;
  const changes = $derived(Object.keys(values).filter((k) => values[k] !== saved[k]));

  $effect(() => {
    void app.revision;
    void load();
  });

  async function load() {
    const s = await guard(api.readSdkSettings());
    if (!s) return;
    settings = s;
    const v: Record<string, string> = {};
    for (const sec of s.sections) for (const st of sec.settings) v[id(sec.name, st.key)] = st.value;
    values = { ...v };
    saved = v;
  }

  async function save() {
    const list = changes.map((k) => {
      const [section, ...rest] = k.split(".");
      return { section, key: rest.join("."), value: values[k] };
    });
    if ((await guard(api.writeSdkSettings(list))) === undefined) return;
    toast("Saved. The game picks this up the next time it starts.");
    await load();
  }

  async function create() {
    await guard(api.createSdkSettings());
    await refresh();
  }

  const isSwitch = (s: Setting) => ["0", "1"].includes(s.default ?? s.value);
  const isKey = (s: Setting) => /key$/i.test(s.key);
  // "SkipIntros" -> "Skip intros", "UILayoutTrace" -> "UI layout trace"
  const words = (key: string) =>
    key.replace(/([a-z0-9])([A-Z])/g, "$1 $2").replace(/([A-Z]+)([A-Z][a-z])/g, "$1 $2")
      .replace(/ ([A-Z][a-z])/g, (m) => m.toLowerCase());
  // Comments read "1 = do this."; the switch already says on/off.
  const describe = (s: Setting) => s.description.replace(/^1 = /, "").replace(/^./, (c) => c.toUpperCase());

  const KEYS: Record<string, string> = {
    "0x70": "F1", "0x71": "F2", "0x72": "F3", "0x73": "F4", "0x74": "F5", "0x75": "F6", "0x76": "F7", "0x77": "F8",
    "0x78": "F9", "0x79": "F10", "0x7a": "F11", "0x7b": "F12", "0": "Off",
  };
</script>

<div class="page">
  <div class="page-head">
    <div>
      <h1>SDK settings</h1>
      <p>What T3SDK changes in the game. Stored in <code>System\T3SDK.ini</code>; the game reads it at start-up.</p>
    </div>
    <div class="row">
      <button class="btn" onclick={() => load()} disabled={!changes.length}>Revert</button>
      <button class="btn primary" onclick={save} disabled={!changes.length}>
        <Icon name="check" />Save{changes.length ? ` (${changes.length})` : ""}
      </button>
    </div>
  </div>

  {#if settings && !settings.exists}
    <div class="card empty">
      <h3>No T3SDK.ini in the game yet</h3>
      <p>It is created when T3SDK is installed. You can also create one with the default settings now.</p>
      <p class="row center">
        <button class="btn primary" onclick={create} disabled={!settings.template}>Create T3SDK.ini</button>
      </p>
    </div>
  {:else if settings}
    <div class="sections">
      {#each settings.sections as section (section.name)}
        <section class="card">
          <h2>{section.name === "T3SDK" ? "General" : section.name}</h2>
          {#each section.settings as s (s.key)}
            {@const k = id(section.name, s.key)}
            <div class="setting">
              <div class="grow">
                <h3>{words(s.key)} {#if values[k] !== saved[k]}<span class="badge warn">changed</span>{/if}</h3>
                <p class="muted">{describe(s)}</p>
              </div>
              {#if isSwitch(s)}
                <Toggle checked={values[k] === "1"} label={s.key} onchange={(on) => (values[k] = on ? "1" : "0")} />
              {:else if isKey(s)}
                <div class="keybox">
                  <input type="text" value={values[k]} spellcheck="false" oninput={(e) => (values[k] = e.currentTarget.value.trim())} />
                  <span class="faint">{KEYS[values[k]?.toLowerCase()] ?? ""}</span>
                </div>
              {:else}
                <input class="text" type="text" value={values[k]} spellcheck="false" oninput={(e) => (values[k] = e.currentTarget.value)} />
              {/if}
            </div>
          {/each}
        </section>
      {/each}
    </div>
  {/if}
</div>

<style>
  .sections {
    display: grid;
    gap: 14px;
    max-width: 920px;
  }

  section {
    padding: 16px 18px 6px;
  }

  section h2 {
    margin-bottom: 4px;
  }

  .setting {
    display: flex;
    align-items: center;
    gap: 18px;
    padding: 12px 0;
    border-top: 1px solid var(--line);
  }

  section h2 + .setting {
    border-top: 0;
  }

  .setting h3 {
    font-family: var(--sans);
    font-size: 14px;
    display: flex;
    gap: 8px;
    align-items: center;
  }

  .setting p {
    font-size: 13px;
    margin-top: 2px;
  }

  .keybox {
    display: flex;
    align-items: center;
    gap: 8px;
    width: 150px;
  }

  .keybox input {
    width: 80px;
  }

  .text {
    width: 200px !important;
  }

  .center {
    justify-content: center;
    margin-top: 12px;
  }
</style>
