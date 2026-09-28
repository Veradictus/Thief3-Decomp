// See curtain.hpp for what this module is for. Raise() and Lift() run in the
// game; the T3SDK_Curtain export runs in the helper process (rundll32), where
// nothing else of the SDK is started (DllMain only acts inside T3Main.exe).
#include "curtain.hpp"

#include "log.hpp"

#include <dwmapi.h>

#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <vector>

extern "C" IMAGE_DOS_HEADER __ImageBase;  // this DLL's own module, without a loader call

namespace t3sdk::curtain {
namespace {

constexpr wchar_t kWindowClass[] = L"T3SDKCurtain";
// Posted by the incoming game once its loading screen is up; wParam is its window.
constexpr UINT kLiftMessage = WM_APP + 1;
constexpr UINT_PTR kCheckTimer = 1;
constexpr UINT kCheckIntervalMs = 100;
// An incoming game window that has covered the monitor this long without
// lifting the curtain (a game without the SDK's lift) gets the screen anyway.
constexpr DWORD kUnliftedWindowMs = 3000;
// The launcher restarts the game in about five seconds; after this the
// curtain gives up (a crashed start, or a quit that looked like a level change).
constexpr DWORD kTimeoutMs = 20000;

RECT g_monitor{};
DWORD g_previousGame = 0;       // the game process that raised the curtain
DWORD g_raisedAt = 0;
DWORD g_nextWindowSeenAt = 0;   // when the incoming game's window first covered the monitor
HBITMAP g_image = nullptr;      // the monitor as the outgoing game left it; null: black

// A top-down 32-bit image the size of `monitor`.
BITMAPINFO ImageFormat(const RECT& monitor) {
    BITMAPINFO format{};
    format.bmiHeader.biSize = sizeof(format.bmiHeader);
    format.bmiHeader.biWidth = monitor.right - monitor.left;
    format.bmiHeader.biHeight = -(monitor.bottom - monitor.top);
    format.bmiHeader.biPlanes = 1;
    format.bmiHeader.biBitCount = 32;
    format.bmiHeader.biCompression = BI_RGB;
    return format;
}

// Copies what `monitor` shows into a new inheritable section, for the helper
// to show. Returns null when that fails (the curtain is then black).
HANDLE CaptureMonitor(const RECT& monitor) {
    const BITMAPINFO format = ImageFormat(monitor);
    const LONG width = format.bmiHeader.biWidth;
    const LONG height = -format.bmiHeader.biHeight;
    SECURITY_ATTRIBUTES inheritable{sizeof(inheritable), nullptr, TRUE};
    HANDLE section = CreateFileMappingW(INVALID_HANDLE_VALUE, &inheritable, PAGE_READWRITE, 0,
                                        DWORD(width) * DWORD(height) * 4, nullptr);
    if (!section) {
        return nullptr;
    }

    // The frames the game just presented reach the screen at the compositor's next pass.
    DwmFlush();

    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    HDC memory = CreateCompatibleDC(screen);
    HBITMAP image = CreateDIBSection(screen, &format, DIB_RGB_COLORS, &bits, section, 0);
    bool copied = false;
    if (image) {
        HGDIOBJ old = SelectObject(memory, image);
        copied = BitBlt(memory, 0, 0, width, height, screen, monitor.left, monitor.top, SRCCOPY) != FALSE;
        GdiFlush();
        SelectObject(memory, old);
        DeleteObject(image);  // the pixels stay in the section
    }
    DeleteDC(memory);
    ReleaseDC(nullptr, screen);

    if (!copied) {
        CloseHandle(section);
        return nullptr;
    }
    return section;
}

bool IsGameProcess(DWORD pid) {
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!process) {
        return false;
    }

    wchar_t path[MAX_PATH];
    DWORD size = MAX_PATH;
    bool game = false;
    if (QueryFullProcessImageNameW(process, 0, path, &size)) {
        const wchar_t* name = wcsrchr(path, L'\\');
        game = _wcsicmp(name ? name + 1 : path, L"T3Main.exe") == 0;
    }
    CloseHandle(process);
    return game;
}

// A visible window of a new T3Main.exe process that covers the monitor: the
// next level's game window, once its borderless setup is done.
BOOL CALLBACK FindNextGameWindow(HWND window, LPARAM found) {
    if (!IsWindowVisible(window)) {
        return TRUE;
    }

    RECT rect;
    GetWindowRect(window, &rect);
    if (!EqualRect(&rect, &g_monitor)) {
        return TRUE;
    }

    DWORD pid = 0;
    GetWindowThreadProcessId(window, &pid);
    if (pid == GetCurrentProcessId() || pid == g_previousGame || !IsGameProcess(pid)) {
        return TRUE;
    }

    *reinterpret_cast<HWND*>(found) = window;
    return FALSE;
}

// Hands the foreground to the incoming game and ends the curtain.
void StepAside(HWND curtain, HWND game) {
    if (game) {
        SetForegroundWindow(game);
    }
    DestroyWindow(curtain);
}

void Paint(HWND window) {
    PAINTSTRUCT paint;
    HDC target = BeginPaint(window, &paint);
    if (g_image) {
        HDC memory = CreateCompatibleDC(target);
        HGDIOBJ old = SelectObject(memory, g_image);
        BitBlt(target, 0, 0, g_monitor.right - g_monitor.left, g_monitor.bottom - g_monitor.top, memory, 0, 0,
               SRCCOPY);
        SelectObject(memory, old);
        DeleteDC(memory);
    } else {
        FillRect(target, &paint.rcPaint, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
    }
    EndPaint(window, &paint);
}

LRESULT CALLBACK CurtainProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case kLiftMessage:
        StepAside(window, reinterpret_cast<HWND>(wParam));
        return 0;

    case WM_TIMER: {
        HWND game = nullptr;
        EnumWindows(&FindNextGameWindow, reinterpret_cast<LPARAM>(&game));
        const DWORD now = GetTickCount();
        if (game && !g_nextWindowSeenAt) {
            g_nextWindowSeenAt = now;
        }

        if (game && now - g_nextWindowSeenAt > kUnliftedWindowMs) {
            StepAside(window, game);
        } else if (now - g_raisedAt > kTimeoutMs) {
            DestroyWindow(window);
        }
        return 0;
    }

    // Any click or key lifts the curtain, so it can never trap the player.
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        DestroyWindow(window);
        return 0;

    // No cursor over the loading screen, as in the game.
    case WM_SETCURSOR:
        SetCursor(nullptr);
        return TRUE;

    case WM_ERASEBKGND:
        return TRUE;  // WM_PAINT covers the whole window

    case WM_PAINT:
        Paint(window);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProcW(window, message, wParam, lParam);
    }
}

}  // namespace

void Raise(const RECT& monitor) {
    wchar_t dll[MAX_PATH];
    GetModuleFileNameW(reinterpret_cast<HMODULE>(&__ImageBase), dll, MAX_PATH);

    // The 32-bit rundll32: a 32-bit process's system directory is SysWOW64 on
    // 64-bit Windows, and this DLL is 32-bit.
    wchar_t rundll32[MAX_PATH];
    GetSystemDirectoryW(rundll32, MAX_PATH);
    wcscat_s(rundll32, L"\\rundll32.exe");

    // The helper inherits the image, and only that of the game's handles.
    HANDLE image = CaptureMonitor(monitor);
    SIZE_T size = 0;
    InitializeProcThreadAttributeList(nullptr, 1, 0, &size);
    std::vector<uint8_t> buffer(size);
    auto attributes = reinterpret_cast<LPPROC_THREAD_ATTRIBUTE_LIST>(buffer.data());
    const bool inherit = image && InitializeProcThreadAttributeList(attributes, 1, 0, &size) &&
                         UpdateProcThreadAttribute(attributes, 0, PROC_THREAD_ATTRIBUTE_HANDLE_LIST, &image,
                                                   sizeof(image), nullptr, nullptr);

    wchar_t commandLine[3 * MAX_PATH];
    swprintf_s(commandLine, L"\"%s\" \"%s\",T3SDK_Curtain %ld %ld %ld %ld %lu %lu", rundll32, dll, monitor.left,
               monitor.top, monitor.right, monitor.bottom, GetCurrentProcessId(),
               inherit ? HandleToULong(image) : 0ul);

    STARTUPINFOEXW startup{};
    startup.StartupInfo.cb = inherit ? sizeof(STARTUPINFOEXW) : sizeof(STARTUPINFOW);
    startup.lpAttributeList = inherit ? attributes : nullptr;
    PROCESS_INFORMATION process{};
    const BOOL started = CreateProcessW(rundll32, commandLine, nullptr, nullptr, inherit,
                                        inherit ? EXTENDED_STARTUPINFO_PRESENT : 0, nullptr, nullptr,
                                        &startup.StartupInfo, &process);
    if (inherit) {
        DeleteProcThreadAttributeList(attributes);
    }
    if (image) {
        CloseHandle(image);  // the helper has its own handle now
    }
    if (!started) {
        T3_LOG("curtain: could not start the helper (error %lu)", GetLastError());
        return;
    }

    AllowSetForegroundWindow(process.dwProcessId);
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    T3_LOG("curtain: raised for the level change, %s", inherit ? "showing the loading screen" : "black");
}

void Lift(HWND game) {
    HWND curtain = FindWindowW(kWindowClass, nullptr);
    if (curtain && PostMessageW(curtain, kLiftMessage, reinterpret_cast<WPARAM>(game), 0)) {
        T3_LOG("curtain: lifted, the loading screen is up");
    }
}

}  // namespace t3sdk::curtain

// rundll32 entry point: "<dll>,T3SDK_Curtain left top right bottom gamePid image".
extern "C" void CALLBACK T3SDK_Curtain(HWND, HINSTANCE, LPSTR arguments, int) {
    using namespace t3sdk::curtain;

    RECT& monitor = g_monitor;
    unsigned long game = 0;
    unsigned long image = 0;
    if (sscanf_s(arguments, "%ld %ld %ld %ld %lu %lu", &monitor.left, &monitor.top, &monitor.right,
                 &monitor.bottom, &game, &image) < 5) {
        return;
    }
    g_previousGame = game;
    g_raisedAt = GetTickCount();

    if (image) {
        const BITMAPINFO format = ImageFormat(monitor);
        void* bits = nullptr;
        g_image = CreateDIBSection(nullptr, &format, DIB_RGB_COLORS, &bits, ULongToHandle(image), 0);
    }

    WNDCLASSW windowClass{};
    windowClass.lpfnWndProc = &CurtainProc;
    windowClass.hInstance = reinterpret_cast<HINSTANCE>(&__ImageBase);
    windowClass.lpszClassName = kWindowClass;
    RegisterClassW(&windowClass);

    // Topmost, so it covers the taskbar too; a tool window has no taskbar button.
    HWND window = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, kWindowClass, L"", WS_POPUP | WS_VISIBLE,
                                  monitor.left, monitor.top, monitor.right - monitor.left,
                                  monitor.bottom - monitor.top, nullptr, nullptr, windowClass.hInstance, nullptr);
    if (!window) {
        return;
    }
    UpdateWindow(window);  // paint the loading screen before anything else happens
    SetForegroundWindow(window);
    SetTimer(window, kCheckTimer, kCheckIntervalMs, nullptr);

    MSG message;
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
}
