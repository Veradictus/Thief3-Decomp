<script lang="ts">
  // Settings: the launcher's version, "Check now", the start-up check switch,
  // and the update that was found.
  import { onMount } from "svelte";
  import Icon from "./Icon.svelte";
  import Toggle from "./Toggle.svelte";
  import UpdateProgress from "./UpdateProgress.svelte";
  import { api, emptyConfig } from "$lib/api";
  import { app, guard, running, saveConfig } from "$lib/app.svelte";
  import { ago, dateTime, firstLink } from "$lib/format";
  import { checkForUpdate, installUpdate, loadUpdaterStatus, RELEASES_URL, updater } from "$lib/update.svelte";

  // Bound to the Settings draft, so saving the other settings keeps this one.
  let { autoCheck = $bindable(null) }: { autoCheck?: boolean | null } = $props();

  onMount(() => {
    void loadUpdaterStatus();
  });

  const status = $derived(updater.status);
  const update = $derived(updater.update);
  const notes = $derived(update ? firstLink(update.notes) : null);

  async function setAuto(on: boolean) {
    autoCheck = on;
    await guard(saveConfig({ ...(app.config ?? emptyConfig), autoUpdateCheck: on }));
  }
</script>

<div class="card updates">
  <div class="row">
    <div class="grow">
      <h3>Updates</h3>
      <p class="muted small">
        T3SDK Launcher {status?.version ?? ""}
        {#if status?.lastCheck}· last checked {ago(status.lastCheck)}{/if}
      </p>
    </div>
    {#if status?.enabled}
      <button class="btn small" onclick={() => checkForUpdate(false)} disabled={updater.checking || updater.installing}>
        <Icon name="refresh" size={14} />{updater.checking ? "Checking…" : "Check now"}
      </button>
    {:else if status}
      <button class="btn small" onclick={() => guard(api.openLink(RELEASES_URL))}>
        <Icon name="link" size={14} />Releases
      </button>
    {/if}
  </div>

  {#if status && !status.enabled}
    <p class="muted small">
      This build cannot update itself (a development build, or one made without the update key). New versions are on the
      releases page.
    </p>
  {:else if update}
    <div class="found">
      <div class="row">
        <Icon name="sparkle" />
        <strong class="grow">Version {update.version} is available</strong>
        {#if update.date}<span class="faint small">{dateTime(update.date)}</span>{/if}
      </div>
      {#if update.notes}<p class="muted small notes">{update.notes}</p>{/if}
      {#if updater.installing}
        <UpdateProgress />
      {:else}
        <div class="row">
          <button class="btn small primary" onclick={installUpdate} disabled={running() !== null}>
            <Icon name="download" size={14} />{status?.portable ? "Download" : "Update and restart"}
          </button>
          {#if notes}
            <button class="btn small ghost" onclick={() => guard(api.openLink(notes))}>
              <Icon name="book" size={14} />Release notes
            </button>
          {/if}
        </div>
        {#if status?.portable}
          <p class="faint small">This is the portable launcher: unzip the new version over this folder.</p>
        {:else}
          <p class="faint small">The installer runs without questions and starts the new launcher when it is done.</p>
        {/if}
      {/if}
    </div>
  {:else if updater.checked && !updater.error}
    <p class="ok small"><Icon name="check" size={14} />The launcher is up to date.</p>
  {:else if updater.error}
    <p class="err small">{updater.error}</p>
  {/if}

  {#if status?.enabled}
    <label class="row switch">
      <Toggle checked={autoCheck !== false} label="Check for updates at start-up" onchange={setAuto} />
      <span>Check for updates when the launcher starts (at most once a day)</span>
    </label>
  {/if}
</div>

<style>
  .updates {
    max-width: 900px;
    margin-top: 16px;
    padding: 14px 16px;
    display: grid;
    gap: 12px;
  }

  .small {
    font-size: 12.5px;
  }

  .found {
    display: grid;
    gap: 8px;
    padding: 12px 14px;
    border-radius: var(--radius-sm);
    border: 1px solid #6b5327;
    background: #1f1a10;
  }

  .found :global(svg) {
    flex: none;
  }

  .notes {
    white-space: pre-line;
  }

  .ok {
    display: flex;
    gap: 6px;
    align-items: center;
    color: var(--ok);
  }

  .err {
    color: var(--err);
  }

  .switch {
    gap: 10px;
    cursor: pointer;
  }
</style>
