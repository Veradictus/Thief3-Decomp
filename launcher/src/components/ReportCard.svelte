<script lang="ts">
  // Settings: collect the logs for a bug report, and open the report form.
  import Icon from "./Icon.svelte";
  import { collectLogs, reportProblem } from "$lib/diag";

  let collecting = $state(false);

  async function collect() {
    collecting = true;
    await collectLogs();
    collecting = false;
  }
</script>

<div class="card report">
  <h3>Something wrong?</h3>
  <p class="muted small">
    "Collect logs" saves one zip with T3SDK.log, T3SDK.ini, the mod list, a listing of the game's System folder, these
    settings and the output of recent tasks. Your user folder and name are taken out. Attach it to a problem report.
  </p>
  <div class="row">
    <button class="btn small" onclick={collect} disabled={collecting}>
      <Icon name="download" size={14} />{collecting ? "Collecting…" : "Collect logs"}
    </button>
    <button class="btn small ghost" onclick={reportProblem}><Icon name="bug" size={14} />Report a problem</button>
  </div>
</div>

<style>
  .report {
    max-width: 900px;
    margin-top: 12px;
    padding: 16px 18px;
    display: grid;
    gap: 10px;
  }

  .small {
    font-size: 12.5px;
  }
</style>
