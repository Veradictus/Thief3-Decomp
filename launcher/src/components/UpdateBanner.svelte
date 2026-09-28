<script lang="ts">
  // "A new launcher version is available", at the foot of the sidebar until it
  // is installed or put off.
  import Icon from "./Icon.svelte";
  import UpdateProgress from "./UpdateProgress.svelte";
  import { app, running } from "$lib/app.svelte";
  import { installUpdate, updater } from "$lib/update.svelte";

  const update = $derived(updater.update);
  const busy = $derived(running() !== null);
</script>

{#if update && (!updater.dismissed || updater.installing)}
  <div class="banner" role="status">
    <div class="row head">
      <Icon name="sparkle" />
      <strong>Update available</strong>
    </div>
    <p class="muted small">Launcher {update.version} (you have {update.currentVersion})</p>
    {#if updater.installing}
      <UpdateProgress />
    {:else}
      <button
        class="btn small primary"
        onclick={installUpdate}
        disabled={busy}
        title={busy ? "Updating restarts the launcher: wait for the running task first" : ""}
      >
        <Icon name="download" size={14} />{updater.status?.portable ? "Download" : "Update and restart"}
      </button>
      <div class="row">
        <button class="btn small ghost" onclick={() => (app.page = "settings")}>Details</button>
        <button class="btn small ghost" onclick={() => (updater.dismissed = true)}>Later</button>
      </div>
    {/if}
  </div>
{/if}

<style>
  .banner {
    display: flex;
    flex-direction: column;
    gap: 7px;
    margin: 0 4px 12px;
    padding: 11px 12px;
    border-radius: var(--radius-sm);
    background: #1f1a10;
    border: 1px solid #6b5327;
  }

  .head {
    gap: 7px;
  }

  .head :global(svg) {
    color: var(--accent-2);
    flex: none;
  }

  .small {
    font-size: 12px;
  }

  .banner > .btn {
    justify-content: center;
  }

  .row .btn {
    flex: 1;
    justify-content: center;
  }
</style>
