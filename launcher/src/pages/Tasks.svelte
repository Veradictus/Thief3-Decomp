<script lang="ts">
  // The job queue and each job's live output.
  import Icon from "$components/Icon.svelte";
  import { cancel, clearFinished, duration, jobs, type Job } from "$lib/app.svelte";

  let output = $state<HTMLPreElement>();
  let follow = $state(true);

  const job = $derived(jobs.list.find((j) => j.key === jobs.selected) ?? null);
  const count = $derived(job?.lines.length ?? 0);

  $effect(() => {
    void count;
    if (follow && output) output.scrollTop = output.scrollHeight;
  });

  function onScroll() {
    if (output) follow = output.scrollTop + output.clientHeight >= output.scrollHeight - 8;
  }

  const label: Record<Job["state"], string> = {
    queued: "Queued",
    running: "Running",
    done: "Done",
    failed: "Failed",
    cancelled: "Cancelled",
  };
  const tone: Record<Job["state"], string> = {
    queued: "",
    running: "info",
    done: "ok",
    failed: "err",
    cancelled: "warn",
  };

  function copy() {
    if (job) void navigator.clipboard.writeText(job.lines.map((l) => l.line).join("\n"));
  }
</script>

<div class="page tasks">
  <div class="page-head">
    <div>
      <h1>Tasks</h1>
      <p>Tools run one at a time, in order. Their output stays here until you clear it.</p>
    </div>
    <button class="btn" onclick={clearFinished}><Icon name="trash" />Clear finished</button>
  </div>

  <div class="split">
    <div class="list card">
      {#each [...jobs.list].reverse() as j (j.key)}
        <button class="job" class:active={j.key === jobs.selected} onclick={() => (jobs.selected = j.key)}>
          <div class="grow">
            <span class="title">{j.title}</span>
            <span class="faint small">{duration(j)}</span>
          </div>
          <span class="badge {tone[j.state]}">{label[j.state]}</span>
        </button>
      {:else}
        <p class="empty">Nothing has run yet.</p>
      {/each}
    </div>

    <div class="console card">
      {#if job}
        <div class="row head">
          <div class="grow">
            <h3>{job.title}</h3>
            {#if job.command}<p class="faint mono cmd" title={job.command}>{job.command}</p>{/if}
          </div>
          {#if job.code !== null && job.state !== "done"}<span class="faint small">exit code {job.code}</span>{/if}
          <button class="btn small ghost" onclick={copy} disabled={!job.lines.length}
            ><Icon name="copy" size={14} />Copy</button
          >
          {#if job.state === "running" || job.state === "queued"}
            <button
              class="btn small danger"
              onclick={() => {
                cancel(job);
              }}><Icon name="stop" size={14} />Cancel</button
            >
          {/if}
        </div>
        <pre bind:this={output} onscroll={onScroll}>{#each job.lines as l, i (i)}<span class:err={l.stream === "stderr"}
              >{l.line}
</span>{/each}{#if job.state === "running"}<span class="cursor">▍</span>{/if}</pre>
      {:else}
        <p class="empty">Select a task to see its output.</p>
      {/if}
    </div>
  </div>
</div>

<style>
  .tasks {
    display: flex;
    flex-direction: column;
    padding-bottom: 24px;
  }

  .split {
    flex: 1;
    min-height: 0;
    display: grid;
    grid-template-columns: 300px 1fr;
    gap: 12px;
  }

  .list {
    overflow: auto;
    padding: 6px;
  }

  .job {
    width: 100%;
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 9px 10px;
    border-radius: var(--radius-sm);
    border: 1px solid transparent;
    background: none;
    text-align: left;
    cursor: pointer;
  }

  .job:hover {
    background: var(--panel-2);
  }

  .job.active {
    background: var(--panel-3);
    border-color: var(--line-2);
  }

  .job .grow {
    display: flex;
    flex-direction: column;
  }

  .title {
    font-weight: 600;
  }

  .small {
    font-size: 12px;
  }

  .console {
    display: flex;
    flex-direction: column;
    min-height: 0;
    overflow: hidden;
  }

  .head {
    padding: 12px 14px;
    border-bottom: 1px solid var(--line);
  }

  .cmd {
    font-size: 11.5px;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
    margin-top: 2px;
  }

  pre {
    flex: 1;
    margin: 0;
    padding: 12px 14px;
    overflow: auto;
    background: #0b0c0e;
    font: 12px/1.55 var(--mono);
    color: #cfcabe;
    white-space: pre-wrap;
    word-break: break-all;
  }

  .err {
    color: #f0a090;
  }

  .cursor {
    color: var(--accent);
    animation: blink 1s steps(2) infinite;
  }

  @keyframes blink {
    50% {
      opacity: 0;
    }
  }
</style>
