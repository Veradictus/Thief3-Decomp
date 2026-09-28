# Console commands

The `Exec`-style console commands known from the executable's code and
strings, organised by which function handles them. All of this is **static**
evidence (found in the executable's code and data) rather than **verified**
(actually typed into a running console); see [engine.md](../engine.md) for
what those labels mean. Addresses are absolute, for the build documented in
[target.md](../target.md).

> [!NOTE]
> How to reach a console to type these commands into is not known yet. No
> console-toggle key or binding has turned up in the code, symbols or
> strings examined so far. T3SDK's own `[T3SDK] Console` setting (see
> [sdk.md](../sdk.md)) opens a *log* window, not the engine's command line,
> and is unrelated to everything below.

## The clock: SIMTIME

`TimeManager::ExecSimTime` (`0x10D3EF30`, named in `symbols.txt`) implements
one command with subcommands, fully covered in [runtime.md](runtime.md) and
[engine.md](../engine.md):

| Command | Effect |
|---|---|
| `SIMTIME SCALE <n>` | Sets the clock's time scale. |
| `SIMTIME SETMIN <seconds>` | Sets the minimum frame step (T3SDK's `SmoothFrames` changes this same value at start-up instead). |
| `SIMTIME SETMAX <seconds>` | Sets the maximum frame step. |
| `SIMTIME PAUSE` / `UNPAUSE` / `TOGGLEPAUSE` | Pause control. |
| `SIMTIME STEP` | Advances by a single step while paused. |

## The viewport: UWindowsViewport::Exec

`UWindowsViewport::Exec` (`0x10C8ADE0`, named in `symbols.txt`) handles
display-related commands. Its structure was confirmed by disassembling the
function and reading the command-token strings it compares against:

| Command | Effect |
|---|---|
| `EndFullscreen` | Calls `UWindowsViewport::EndFullscreen` (`0x10C86630`). |
| `ToggleFullscreen` | Calls `UWindowsViewport::ToggleFullscreen` (`0x10C87560`). |
| `GetCurrentRes` | Logs the current resolution as `WIDTHxHEIGHT`. |
| `GetCurrentColorDepth` | Logs the current colour depth as a number. |
| `GetColorDepths` | Logs `32` — the only colour depth the game lists. |
| `GetCurrentRenderDevice` | Logs the current render device's name. |
| `GetRes` | Logs `GetRes command disabled.` and does nothing else — present, but deliberately turned off in this build. |
| `SETRES <width> <height> [num_multisamples]` | Parses the arguments and resizes the device (leading to `UD3DRenderDevice::SetRes`, `0x10C84070`); if the width or height do not parse, it instead logs a usage message, and if the resize itself fails it falls back to `EndFullscreen`. |
| `Preferences` | Opens (or focuses, if already open) a window of class `AdvancedOptionsTitle`, instantiated as an object named `Preferences` — by the class name, likely the advanced video/audio options dialog; not confirmed further. |
| `Bug` | Temporarily leaves fullscreen, calls an unidentified function (`0x10DDAA40`), then restores the previous fullscreen state — consistent with capturing a screenshot or bug report, but that function is not analysed. |

## Engine-level commands

An unnamed function at `0x10AEB6D0` (found by tracing references to these
commands' strings, not yet given a class or a name in `symbols.txt`)
handles a further set of commands that are not specific to the viewport:

| Command | Effect |
|---|---|
| `MEMSTAT` | Logs available/total physical, page-file and virtual memory (via Win32's `GlobalMemoryStatus`) and the current memory load percentage. |
| `RES_DUMPSTATS` | Calls a virtual method on a singleton object (accessor at `0x10DB58F0`) — by the name, a resource-manager statistics dump; not otherwise identified. |
| `CONFIGHASH` | Calls `Config::Instance()` (`0x10911950`) then an unnamed function at `0x109102B0` — an address among the other named `Config::` members in [engine.md](../engine.md), so likely part of that class; presumably computes and logs a hash of the loaded configuration. |
| `EXIT` / `QUIT` | Logs `Closing by request`, then requests the engine exit the same way `appRequestExit(0)` does (see [runtime.md](runtime.md)): posts `WM_QUIT` and sets the exit flag. |
| `RELAUNCH <arguments>` | Logs the game's own module path, then calls `ShellExecuteA` to start that same executable again with `<arguments>` as its command line, and requests exit exactly as `EXIT`/`QUIT` do above — restarting the game with different arguments. |
| `DIR` | Builds and logs two sorted lists of resource entries (name and size); the two categories are not identified. |
| `DEBUG CRASH` | Logs `Unreal crashed at your request` through one of the engine's output-device globals; whether this call chain actually terminates the process, as a real fatal-error log line would, is not confirmed here. |
| `DEBUG GPF` | Logs `Unreal crashing with voluntary GPF`, then writes through a null pointer — a genuine, deliberate access-violation crash. |
| `DEBUG EATMEM` | Logs `Eating up all available memory`, then loops forever allocating and zeroing 64 KB blocks with no exit condition, until an allocation fails or the process is killed. |

`RELAUNCH`, `DEBUG CRASH` and `DEBUG GPF` are destructive or exit the game
outright; `DEBUG EATMEM` does not return. None of these should be bound to
anything a player could trigger by accident.
