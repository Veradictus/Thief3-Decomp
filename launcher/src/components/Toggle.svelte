<script lang="ts">
  let { checked = $bindable(false), disabled = false, label = "", onchange }: {
    checked?: boolean;
    disabled?: boolean;
    label?: string;
    onchange?: (checked: boolean) => void;
  } = $props();
</script>

<button class="toggle" class:on={checked} {disabled} role="switch" aria-checked={checked} aria-label={label}
  onclick={() => { checked = !checked; onchange?.(checked); }}>
  <span class="knob"></span>
</button>

<style>
  .toggle {
    position: relative;
    width: 40px;
    height: 22px;
    flex: none;
    border-radius: 99px;
    border: 1px solid var(--line-2);
    background: #101216;
    cursor: pointer;
    padding: 0;
    transition: background 0.15s, border-color 0.15s;
  }

  .toggle.on {
    background: #3a2f18;
    border-color: #8d6c2c;
  }

  .toggle:disabled {
    opacity: 0.45;
    cursor: default;
  }

  .knob {
    position: absolute;
    top: 3px;
    left: 3px;
    width: 14px;
    height: 14px;
    border-radius: 50%;
    background: var(--muted);
    transition: transform 0.15s, background 0.15s;
  }

  .on .knob {
    transform: translateX(18px);
    background: var(--accent-2);
  }
</style>
