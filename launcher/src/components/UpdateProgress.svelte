<script lang="ts">
  // The update download: a bar while the size is known, then "Installing".
  import { bytes, percent } from "$lib/format";
  import { updater } from "$lib/update.svelte";

  const p = $derived(updater.progress);
  const share = $derived(p ? percent(p.downloaded, p.total) : null);
</script>

<div class="progress">
  <div class="bar">
    <span class:indeterminate={share === null && !p?.finished} style:width="{p?.finished ? 100 : (share ?? 30)}%"
    ></span>
  </div>
  <p class="muted small">
    {#if p?.finished}
      Installing… the launcher restarts when it is done.
    {:else if share !== null}
      Downloading… {share}%
    {:else}
      Downloading… {p?.downloaded ? bytes(p.downloaded) : ""}
    {/if}
  </p>
</div>

<style>
  .progress {
    display: grid;
    gap: 6px;
  }

  .bar {
    height: 6px;
    border-radius: 99px;
    background: #101216;
    border: 1px solid var(--line-2);
    overflow: hidden;
  }

  .bar span {
    display: block;
    height: 100%;
    background: linear-gradient(90deg, var(--accent), var(--accent-2));
    transition: width 0.2s;
  }

  .bar span.indeterminate {
    animation: slide 1.2s ease-in-out infinite;
  }

  @keyframes slide {
    from {
      transform: translateX(-100%);
    }
    to {
      transform: translateX(340%);
    }
  }

  .small {
    font-size: 12.5px;
  }
</style>
