// See log.hpp for what this module is for.
#include "log.hpp"

#include <windows.h>

#include <cstdio>
#include <mutex>

namespace t3sdk::log {
namespace {

std::mutex g_mutex;
FILE* g_file = nullptr;
HANDLE g_console = nullptr;

}  // namespace

void Open(const std::filesystem::path& file, bool console) {
    std::lock_guard lock(g_mutex);
    // Keep diagnostics from earlier runs; the owner can clear this file when wanted.
    g_file = _wfopen(file.c_str(), L"a");
    if (console && AllocConsole()) {
        SetConsoleTitleW(L"T3SDK");
        g_console = GetStdHandle(STD_OUTPUT_HANDLE);
    }
}

void WriteV(const char* tag, const char* fmt, va_list args) {
    char message[2048];
    vsnprintf(message, sizeof(message), fmt, args);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char line[2200];
    int n = snprintf(line, sizeof(line), "%02u:%02u:%02u.%03u [%s] %s\n", t.wHour, t.wMinute, t.wSecond,
                     t.wMilliseconds, tag, message);
    if (n < 0) {
        return;
    }
    n = n < int(sizeof(line)) ? n : int(sizeof(line)) - 1;

    std::lock_guard lock(g_mutex);
    if (g_file) {
        fwrite(line, 1, size_t(n), g_file);
        fflush(g_file);
    }
    if (g_console) {
        DWORD written;
        WriteConsoleA(g_console, line, DWORD(n), &written, nullptr);
    }
    OutputDebugStringA(line);
}

void Write(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    WriteV(tag, fmt, args);
    va_end(args);
}

}  // namespace t3sdk::log
