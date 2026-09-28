<script lang="ts">
  // Shown while .t3mod files are dragged over the window; dropping them
  // installs them (lib/mods.svelte.ts), from any page.
  import { onMount } from "svelte";
  import Icon from "./Icon.svelte";
  import { listenForMods, mods } from "$lib/mods.svelte";

  onMount(() => {
    void listenForMods();
  });
</script>

{#if mods.dragging}
  <div class="drop" aria-hidden="true">
    <div class="box">
      <Icon name="download" size={30} />
      <h2>Drop to install</h2>
      <p class="muted">.t3mod packages go into System\mods and are switched on.</p>
    </div>
  </div>
{/if}

<style>
  .drop {
    position: fixed;
    inset: 0;
    z-index: 20;
    display: grid;
    place-items: center;
    background: #0d0e11cc;
    backdrop-filter: blur(3px);
    pointer-events: none;
  }

  .box {
    display: grid;
    justify-items: center;
    gap: 8px;
    padding: 36px 56px;
    border: 2px dashed var(--accent);
    border-radius: 16px;
    background: #17191ddd;
    color: var(--accent-2);
  }
</style>
