export const meta = {
  name: 't3-swarm',
  description: 'Run a batch of t3-matcher workers over the matching queue in bands, refilling each slot as it frees, and stamp families as matches land',
  whenToUse: 'The lead runs a swarm of matching workers (docs/agent-workflow.md, "Running a swarm as a workflow"). Then: python tools/agent/sweep.py "<prefix>-*".',
  phases: [
    { title: 'Swarm', detail: 'workers claim, match and defer through tools/agent; a stamp helper runs between them' },
  ],
}

// args (all optional): {
//   prefix: 's4',                       worker ids are <prefix>-<band letter><nn>; never reuse a prefix
//   python: '.venv/Scripts/python',     the interpreter the workers and the stamp helper run the tools with
//   bands: {head: 10, main: 16, big: 6, second: 0},   workers per band (0 leaves a band out)
//   smoke: true,                        one main-band worker on two functions, nothing else
//   stampEvery: 8,                      a stamp helper after every this many workers (0: none)
// }
const A = args || {}
const PREFIX = A.prefix || 'sw'
const PY = A.python || '.venv/Scripts/python'
const STAMP_EVERY = A.stampEvery === undefined ? 8 : A.stampEvery

// The bands of docs/agent-workflow.md. --by-class keeps a worker on one class for its claims.
const BANDS = {
  head:   { letter: 'h', model: 'sonnet', filters: '--max-size 31', n: 20, count: 4, cap: 5 },
  main:   { letter: 'm', model: 'sonnet', filters: '--min-size 32 --max-size 79 --by-class', n: 6, count: 2, cap: 8 },
  big:    { letter: 'b', model: 'opus',   filters: '--min-size 80 --by-class', n: 4, count: 1, cap: 10 },
  // Deferrals the lead unblocked (next.py requeue) or worth a different model: Opus retries Sonnet's.
  second: { letter: 'r', model: 'opus',   filters: '--only-deferred', n: 4, count: 1, cap: 8 },
}
const counts = A.smoke ? { main: 1 } : Object.assign({ head: 10, main: 16, big: 6, second: 0 }, A.bands || {})

// Interleave the bands so every stretch of the run mixes models and sizes.
const queues = Object.keys(BANDS).map(band => {
  const list = []
  for (let i = 1; i <= (counts[band] || 0); i++) {
    const b = BANDS[band]
    list.push({ kind: 'worker', band, model: b.model, filters: b.filters,
                n: A.smoke ? 2 : b.n, count: A.smoke ? 1 : b.count, cap: b.cap,
                id: `${PREFIX}-${b.letter}${String(i).padStart(2, '0')}` })
  }
  return list
})
const items = []
let made = 0
while (queues.some(q => q.length)) {
  for (const q of queues) {
    if (!q.length) continue
    items.push(q.shift())
    made++
    if (STAMP_EVERY && !A.smoke && made % STAMP_EVERY === 0) items.push({ kind: 'stamp', id: `stamp-${made}` })
  }
}
if (STAMP_EVERY && !A.smoke && items.length) items.push({ kind: 'stamp', id: 'stamp-last' })

const REPORT = {
  type: 'object',
  properties: {
    agent: { type: 'string' },
    matched: { type: 'array', items: { type: 'string' } },
    deferred: { type: 'array', items: { type: 'object', properties: {
      addr: { type: 'string' }, best: { type: 'number' }, why: { type: 'string' } }, required: ['addr'] } },
    needs: { type: 'array', items: { type: 'string' } },
    idioms: { type: 'array', items: { type: 'string' } },
    empty: { type: 'boolean', description: 'true when a claim printed "empty": true' },
  },
  required: ['agent', 'matched', 'deferred'],
}
const STAMPED = {
  type: 'object',
  properties: { stamped: { type: 'number' }, failed: { type: 'number' }, skipped: { type: 'number' },
                note: { type: 'string' } },
  required: ['stamped', 'failed'],
}

const emptyBands = new Set()
const tally = { workers: 0, matched: 0, deferred: 0, stamped: 0, emptyRuns: 0 }
const needs = new Map()
const idioms = new Map()

phase('Swarm')
log(`${items.filter(i => i.kind === 'worker').length} workers (${Object.entries(counts).filter(([, n]) => n).map(([b, n]) => `${b} ${n}`).join(', ')}), ids ${PREFIX}-*`)

const results = await pipeline(items, async item => {
  if (item.kind === 'stamp') {
    const r = await agent(
      `From the repository root, run exactly this one command and nothing else: ${PY} tools/agent/clusters.py stamp\n` +
      'It prints JSON whose "summary" holds the counts of stamped, failed and skipped. Return those counts; ' +
      'if the command fails, return zeros and the last line of its error as note.',
      { label: item.id, phase: 'Swarm', model: 'haiku', effort: 'low', schema: STAMPED })
    if (r) {
      tally.stamped += r.stamped || 0
      log(`${item.id}: ${r.stamped} stamped, ${r.failed} failed${r.note ? ` (${r.note})` : ''}`)
    }
    return r && { kind: 'stamp', ...r }
  }
  if (emptyBands.has(item.band)) return null  // the band's queue ran dry: no more workers for it
  const r = await agent(
    `Read tools/agent/worker.md and follow it exactly. ID=${item.id} FILTERS=${item.filters} N=${item.n} ` +
    `COUNT=${item.count} CAP=${item.cap} PY=${PY}`,
    { label: `${item.id} ${item.band}`, phase: 'Swarm', agentType: 't3-matcher', model: item.model, schema: REPORT })
  if (!r) return null
  tally.workers++
  tally.matched += (r.matched || []).length
  tally.deferred += (r.deferred || []).length
  if (r.empty && !(r.matched || []).length && !(r.deferred || []).length) {
    tally.emptyRuns++
    emptyBands.add(item.band)
    log(`${item.band}: the queue is empty for this band; its remaining workers are skipped`)
  }
  for (const x of r.needs || []) needs.set(x, (needs.get(x) || 0) + 1)
  for (const x of r.idioms || []) idioms.set(x, (idioms.get(x) || 0) + 1)
  log(`${item.id}: ${(r.matched || []).length} matched, ${(r.deferred || []).length} deferred ` +
      `(total ${tally.matched} matched, ${tally.deferred} deferred, ${tally.workers} workers)`)
  return { kind: 'worker', band: item.band, model: item.model, ...r }
})

const workers = results.filter(r => r && r.kind === 'worker')
const byBand = {}
for (const r of workers) {
  const b = byBand[r.band] || (byBand[r.band] = { workers: 0, matched: 0, deferred: 0 })
  b.workers++
  b.matched += (r.matched || []).length
  b.deferred += (r.deferred || []).length
}
const top = m => [...m.entries()].sort((a, b) => b[1] - a[1]).slice(0, 15).map(([k, n]) => (n > 1 ? `${n}x ` : '') + k)
const skipped = items.filter(i => i.kind === 'worker').length - workers.length
if (skipped) log(`${skipped} workers did not run (an empty band, or skipped)`)
return {
  prefix: PREFIX,
  sweep: `python tools/agent/sweep.py "${PREFIX}-*"`,
  ...tally,
  byBand,
  skippedWorkers: skipped,
  needs: top(needs),
  idioms: top(idioms),
  deferrals: workers.flatMap(r => (r.deferred || []).map(d => ({ agent: r.agent, ...d }))).slice(0, 60),
}
