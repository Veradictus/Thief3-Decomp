#pragma once

// T3SDK.log: a single mutex-protected sink shared by the SDK's own T3_LOG
// calls and every mod's Log call (see t3sdk.h), optionally echoed to a
// console window and to the debugger.

#include <cstdarg>
#include <filesystem>

namespace t3sdk::log {

// Opens `file` (appending to it; the owner can clear it when that's wanted).
// With `console`, also shows a console window.
void Open(const std::filesystem::path& file, bool console);

// Writes one line: "hh:mm:ss.mmm [tag] message". Thread-safe; flushed at once so
// the log survives a crash.
void Write(const char* tag, const char* fmt, ...);
void WriteV(const char* tag, const char* fmt, va_list args);

}  // namespace t3sdk::log

#define T3_LOG(...) ::t3sdk::log::Write("sdk", __VA_ARGS__)
