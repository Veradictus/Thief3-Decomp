<script lang="ts">
  // Line icons, drawn for the launcher (24x24 grid, stroke only).
  let { name, size = 16 }: { name: string; size?: number } = $props();

  const paths: Record<string, string> = {
    play: "M7 4.5v15l12-7.5z",
    map: "M9 4 3.5 6v14L9 18l6 2 5.5-2V4L15 6zM9 4v14M15 6v14",
    puzzle:
      "M10 4.5a2 2 0 1 1 4 0V6h4v4h-1.5a2 2 0 1 0 0 4H18v4h-4v-1.5a2 2 0 1 0-4 0V18H6v-4h1.5a2 2 0 1 0 0-4H6V6h4z",
    sliders: "M4 7h10M18 7h2M4 17h4M12 17h8M14 4.5v5M8 14.5v5",
    terminal: "M4 5.5h16v13H4zM7.5 10l2.5 2-2.5 2M12.5 14.5h4",
    gear: "M12 9a3 3 0 1 0 0 6 3 3 0 0 0 0-6zM19.4 13.5l1.6 1-2 3.4-1.8-.7a7 7 0 0 1-2 1.2l-.3 1.9h-3.8l-.3-1.9a7 7 0 0 1-2-1.2l-1.8.7-2-3.4 1.6-1a7 7 0 0 1 0-3l-1.6-1 2-3.4 1.8.7a7 7 0 0 1 2-1.2l.3-1.9h3.8l.3 1.9a7 7 0 0 1 2 1.2l1.8-.7 2 3.4-1.6 1a7 7 0 0 1 0 3z",
    folder: "M3.5 6.5h6l2 2h9v10h-17z",
    refresh: "M19.5 12a7.5 7.5 0 1 1-2.2-5.3M19.5 4.5v4h-4",
    download: "M12 4v11M7.5 10.5 12 15l4.5-4.5M5 19.5h14",
    upload: "M12 15V4M7.5 8.5 12 4l4.5 4.5M5 19.5h14",
    box: "M12 3.5 20 8v8l-8 4.5L4 16V8zM4 8l8 4.5L20 8M12 12.5v8",
    edit: "M4.5 19.5h4l10-10-4-4-10 10zM13 7l4 4",
    eye: "M2.5 12s3.5-6.5 9.5-6.5 9.5 6.5 9.5 6.5-3.5 6.5-9.5 6.5S2.5 12 2.5 12zM12 9.5a2.5 2.5 0 1 0 0 5 2.5 2.5 0 0 0 0-5z",
    undo: "M8.5 5 4 9.5 8.5 14M4.5 9.5H14a5.5 5.5 0 0 1 0 11h-3",
    check: "M5 12.5l4.5 4.5L19 7.5",
    x: "M6 6l12 12M18 6 6 18",
    alert: "M12 4 21 19.5H3zM12 10v4.5M12 17v.5",
    stop: "M6.5 6.5h11v11h-11z",
    link: "M10 14a4 4 0 0 0 5.7 0l3-3a4 4 0 0 0-5.7-5.7l-1 1M14 10a4 4 0 0 0-5.7 0l-3 3a4 4 0 0 0 5.7 5.7l1-1",
    search: "M10.5 4a6.5 6.5 0 1 0 0 13 6.5 6.5 0 0 0 0-13zM15.5 15.5 20 20",
    hammer: "M13.5 6.5 17 3l4 4-3.5 3.5M13.5 6.5l4 4M13.5 6.5 4 16l4 4 9.5-9.5",
    shield: "M12 3.5 19.5 6v6c0 4.5-3.2 7.6-7.5 8.5-4.3-.9-7.5-4-7.5-8.5V6z",
    trash: "M5 7h14M10 4h4M7 7l1 13h8l1-13",
    copy: "M9 9h10.5v10.5H9zM5 15V4.5h10.5",
    chevron: "M9 6l6 6-6 6",
    discord:
      "M8 16.5c-2.5-.5-4-1.5-4-1.5.2-4 1.5-7.2 3-9 1.2-.6 2.4-1 3.5-1.1l.5 1a11 11 0 0 1 2 0l.5-1c1.1.1 2.3.5 3.5 1.1 1.5 1.8 2.8 5 3 9 0 0-1.5 1-4 1.5l-1-1.5M9.5 12.5h.01M14.5 12.5h.01M7.5 15c3 1.5 6 1.5 9 0",
    book: "M4.5 5.5c2.5-1 5-1 7.5.5 2.5-1.5 5-1.5 7.5-.5v13c-2.5-1-5-1-7.5.5-2.5-1.5-5-1.5-7.5-.5zM12 6v13",
  };
</script>

<svg
  width={size}
  height={size}
  viewBox="0 0 24 24"
  fill="none"
  stroke="currentColor"
  stroke-width="1.7"
  stroke-linecap="round"
  stroke-linejoin="round"
  aria-hidden="true"
>
  {#if name === "play"}
    <path d={paths.play} fill="currentColor" stroke="none" />
  {:else}
    <path d={paths[name] ?? paths.alert} />
  {/if}
</svg>
