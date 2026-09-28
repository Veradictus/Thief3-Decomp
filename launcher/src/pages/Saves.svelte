<script lang="ts">
  // Backups of the game's saves: zips of the whole SaveGames folder in the
  // launcher's per-user folder. Restoring one backs up the current saves first.
  import Icon from "$components/Icon.svelte";
  import Toggle from "$components/Toggle.svelte";
  import { api, emptyConfig, type Backup, type BackupList, type SavesInfo } from "$lib/api";
  import { app, guard, saveConfig, toast } from "$lib/app.svelte";
  import { ago, bytes, dateTime } from "$lib/format";

  let info = $state<SavesInfo | null>(null);
  let list = $state<BackupList | null>(null);
  let label = $state("");
  let working = $state<"" | "backup" | "restore">("");
  let confirm = $state<{ file: string; action: "restore" | "delete" } | null>(null);

  $effect(() => {
    void app.revision;
    void load();
  });

  async function load() {
    const [i, l] = await Promise.all([guard(api.savesInfo()), guard(api.listSaveBackups())]);
    info = i ?? info;
    list = l ?? list;
  }

  const running = $derived(app.overview?.running ?? false);
  const folder = $derived(info?.folder ?? null);
  const s = $derived(info?.summary ?? null);
  const sizeAndAge = $derived(
    s ? [bytes(s.size), s.newest ? `last saved ${ago(s.newest)}` : ""].filter(Boolean).join(" · ") : "",
  );

  /** The labels of the launcher's own backups (saves.rs). */
  const automatic = ["before restore", "before launch"];

  /** "6 saves · 41.4 MB, 25.7 MB zipped · 3 h ago" */
  function details(b: Backup): string {
    const saves = b.saves === null ? [] : [`${b.saves.toString()} saves`];
    const size = b.size === null ? bytes(b.bytes) : `${bytes(b.size)}, ${bytes(b.bytes)} zipped`;
    return [...saves, size, ago(b.created)].join(" · ");
  }

  async function backUp() {
    working = "backup";
    const made = await guard(api.createSaveBackup(label.trim() || null));
    working = "";
    if (made) {
      toast(`Backed up ${(made.saves ?? 0).toString()} saves.`);
      label = "";
      await load();
    }
  }

  async function restore(b: Backup) {
    confirm = null;
    working = "restore";
    const done = await guard(api.restoreSaveBackup(b.file));
    working = "";
    if (done) {
      toast(
        done.before
          ? `Restored. The saves it replaced are in the backup of ${dateTime(done.before.created)}.`
          : "Restored.",
      );
      await load();
    }
  }

  async function remove(b: Backup) {
    confirm = null;
    if ((await guard(api.deleteSaveBackup(b.file))) !== undefined) await load();
  }

  async function setBeforeLaunch(on: boolean) {
    await guard(saveConfig({ ...(app.config ?? emptyConfig), backupBeforeLaunch: on }));
  }
</script>

<div class="page">
  <div class="page-head">
    <h1>Saves</h1>
    <div class="row">
      <button class="btn" onclick={load}><Icon name="refresh" />Refresh</button>
      <button class="btn" onclick={() => guard(api.openSavesFolder("backups"))}><Icon name="folder" />Backups</button>
    </div>
    <p>
      Back up the game's saved games and put them back. Backups are zips in your user profile, not in the game folder;
      restoring one backs up the current saves first.
    </p>
  </div>

  <section class="card summary">
    <div class="row">
      <div class="icon"><Icon name="archive" size={17} /></div>
      <div class="grow">
        {#if folder && info?.exists}
          <h3>{s?.count ?? 0} saves <span class="muted small">· {sizeAndAge}</span></h3>
          <p class="mono faint small clip" title={folder.path}>{folder.path}</p>
        {:else if folder}
          <h3>No saves folder</h3>
          <p class="muted small clip">
            <span class="mono">{folder.path}</span> (set in Settings) does not exist.
          </p>
        {:else}
          <h3>No saves yet</h3>
          <p class="muted small">
            The game creates its SaveGames folder with the first save. If it keeps them somewhere unusual, set the
            folder in Settings.
          </p>
        {/if}
      </div>
      {#if folder}<span class="badge" title="Where the folder was found">{folder.source}</span>{/if}
      <button class="btn small" onclick={() => guard(api.openSavesFolder("saves"))} disabled={!info?.exists}>
        <Icon name="folder" size={14} />Open
      </button>
    </div>
    <div class="row make">
      <input
        type="text"
        placeholder="Label (optional), e.g. before the Cathedral"
        maxlength="60"
        bind:value={label}
        onkeydown={(e) => {
          if (e.key === "Enter" && info?.exists && !working) void backUp();
        }}
      />
      <button class="btn primary" onclick={backUp} disabled={!info?.exists || working !== ""}>
        <Icon name="archive" />{working === "backup" ? "Backing up…" : "Back up now"}
      </button>
    </div>
    <label class="row option">
      <Toggle
        checked={app.config?.backupBeforeLaunch ?? false}
        label="Back up before starting the game"
        onchange={setBeforeLaunch}
      />
      <span>Back up when the launcher starts the game (only if the saves changed; the last 10 are kept)</span>
    </label>
  </section>

  {#if running}
    <div class="note card"><Icon name="alert" />Thief is running. Quit the game before restoring a backup.</div>
  {/if}

  <!-- As tall as its backups, and no taller than the window: then it scrolls. -->
  <div class="list card">
    {#each list?.backups ?? [] as b (b.file)}
      <div class="backup">
        <div class="grow">
          <h3 class="clip">
            {dateTime(b.created)}
            {#if b.label}<span class="badge" class:info={automatic.includes(b.label)}>{b.label}</span>{/if}
          </h3>
          <p class="faint small clip">{details(b)}</p>
        </div>
        {#if confirm?.file === b.file}
          <span class="muted small">
            {confirm.action === "restore" ? "Replace the current saves with this backup?" : "Delete this backup?"}
          </span>
          {#if confirm.action === "restore"}
            <button class="btn small primary" onclick={() => restore(b)}>Restore</button>
          {:else}
            <button class="btn small danger" onclick={() => remove(b)}>Delete</button>
          {/if}
          <button class="btn small ghost" onclick={() => (confirm = null)}>Cancel</button>
        {:else}
          <button
            class="btn small"
            disabled={running || working !== "" || !folder}
            onclick={() => (confirm = { file: b.file, action: "restore" })}
            ><Icon name="undo" size={14} />Restore</button
          >
          <button
            class="btn small ghost danger"
            disabled={working !== ""}
            title="Delete this backup"
            onclick={() => (confirm = { file: b.file, action: "delete" })}><Icon name="trash" size={14} /></button
          >
        {/if}
      </div>
    {:else}
      <div class="empty">
        <h3>No backups yet</h3>
        <p>"Back up now" zips the whole saves folder. Backups stay until you delete them.</p>
      </div>
    {/each}
  </div>
  {#if list}<p class="faint small where clip">Backups are kept in <span class="mono">{list.dir}</span>.</p>{/if}
</div>

<style>
  /* minmax(0, 1fr): the folder path is clipped rather than widening the card. */
  .summary {
    display: grid;
    grid-template-columns: minmax(0, 1fr);
    gap: 10px;
    padding: 12px 16px;
    margin-bottom: 12px;
  }

  .summary > .row {
    gap: 12px;
  }

  .icon {
    width: 34px;
    height: 34px;
    flex: none;
    border-radius: 8px;
    display: grid;
    place-items: center;
    background: #2a2416;
    color: var(--accent-2);
  }

  .clip {
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }

  .small {
    font-size: 12.5px;
  }

  h3 .small,
  h3 .badge {
    font-family: var(--sans);
    font-weight: 400;
    margin-left: 4px;
  }

  .option {
    gap: 10px;
    color: var(--muted);
    font-size: 13px;
    cursor: pointer;
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

  .list {
    flex: 0 1 auto;
    min-height: 0;
    overflow: auto;
  }

  .backup {
    display: flex;
    align-items: center;
    gap: 10px;
    min-width: 0;
    padding: 10px 16px;
    border-top: 1px solid var(--line);
  }

  .backup:first-child {
    border-top: 0;
  }

  .backup p {
    margin-top: 2px;
  }

  .where {
    margin-top: 8px;
  }
</style>
