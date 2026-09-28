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
    <div>
      <h1>Saves</h1>
      <p>
        Back up the game's saved games and put them back. Backups are zips in your user profile, not in the game folder.
        Restoring one backs up the current saves first.
      </p>
    </div>
    <div class="row">
      <button class="btn" onclick={load}><Icon name="refresh" />Refresh</button>
      <button class="btn" onclick={() => guard(api.openSavesFolder("backups"))}><Icon name="folder" />Backups</button>
    </div>
  </div>

  <section class="card summary">
    <div class="icon"><Icon name="archive" size={20} /></div>
    <div class="grow">
      {#if folder && info?.exists}
        <h3>{s?.count ?? 0} saves <span class="muted small">· {sizeAndAge}</span></h3>
        <p class="mono faint path" title={folder.path}>{folder.path}</p>
      {:else if folder}
        <h3>No saves folder</h3>
        <p class="muted small">
          <span class="mono">{folder.path}</span> (set in Settings) does not exist.
        </p>
      {:else}
        <h3>No saves yet</h3>
        <p class="muted small">
          The game creates its SaveGames folder with the first save. If it keeps them somewhere unusual, set the folder
          in Settings.
        </p>
      {/if}
    </div>
    {#if folder}<span class="badge" title="Where the folder was found">{folder.source}</span>{/if}
    <button class="btn small" onclick={() => guard(api.openSavesFolder("saves"))} disabled={!info?.exists}>
      <Icon name="folder" size={14} />Open
    </button>
  </section>

  <section class="card make">
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
  </section>

  <label class="row option">
    <Toggle
      checked={app.config?.backupBeforeLaunch ?? false}
      label="Back up before starting the game"
      onchange={setBeforeLaunch}
    />
    <span>Back up the saves when the launcher starts the game (only if they changed; the last 10 are kept)</span>
  </label>

  {#if running}
    <div class="note card"><Icon name="alert" />Thief is running. Quit the game before restoring a backup.</div>
  {/if}

  <div class="card">
    {#each list?.backups ?? [] as b (b.file)}
      <div class="backup">
        <div class="grow">
          <h3>
            {dateTime(b.created)}
            {#if b.label}<span class="badge" class:info={automatic.includes(b.label)}>{b.label}</span>{/if}
          </h3>
          <p class="faint small">{details(b)}</p>
        </div>
        {#if confirm?.file === b.file}
          <span class="muted small ask">
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
  {#if list}<p class="faint small where">Backups are kept in <span class="mono">{list.dir}</span>.</p>{/if}
</div>

<style>
  .summary {
    display: flex;
    align-items: center;
    gap: 14px;
    padding: 14px 18px;
  }

  .icon {
    width: 40px;
    height: 40px;
    border-radius: 9px;
    display: grid;
    place-items: center;
    background: #2a2416;
    color: var(--accent-2);
    flex: none;
  }

  .path {
    margin-top: 2px;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
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

  .make {
    display: flex;
    gap: 8px;
    padding: 12px 14px;
    margin-top: 12px;
  }

  .option {
    gap: 10px;
    margin: 14px 2px;
    color: var(--muted);
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

  .backup {
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 12px 18px;
    border-top: 1px solid var(--line);
  }

  .backup:first-child {
    border-top: 0;
  }

  .backup p {
    margin-top: 2px;
  }

  .ask {
    margin-right: 4px;
  }

  .where {
    margin-top: 10px;
  }
</style>
