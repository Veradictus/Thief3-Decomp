// See menu.hpp for what this module is for.
#include "menu.hpp"

#include "sdk.hpp"
#include "log.hpp"

#include <MinHook.h>
#include <windows.h>

#include <cstdint>
#include <cstring>

namespace t3sdk::menu {
namespace {

// ---- version label patch -------------------------------------------------------
// FUN_10b28b70 formats the bottom-left version line with two `%s` arguments
// at 0x10b28e28. Only that call's immediate is redirected. The original
// localised version and other argument remain owned/formatted by the engine.
constexpr uintptr_t kFormatOperand = 0x10B28E29;
constexpr uint8_t kExpectedInstruction[] = {0x68, 0x20, 0x0e, 0xe7, 0x10};
constexpr uintptr_t kOriginalFormat = 0x10E70E20;
const char kModdedFormat[] = "%s %s [Modded - T3SDK " T3SDK_VERSION "]";

// ---- input diagnostics ----------------------------------------------------------
constexpr uintptr_t kMainMenuInput = 0x10B28750;
constexpr uintptr_t kWindowInput = 0x10A52DD0;
constexpr uintptr_t kPopupVtables[] = {0x10E696A8, 0x10E7FB08};

// Offsets into the main-menu/popup window objects, found by observation for
// this diagnostic; not in docs/engine.md and not exposed to mods.
constexpr uint32_t kChildCountOffset = 0xB8;
constexpr uint32_t kChildrenOffset = 0xC0;
constexpr uint32_t kSelectedOffset = 0xC4;

using InputFn = int(__fastcall*)(void* self, void* edx, int event, void* arg3, void* arg4);
InputFn g_mainMenuInput = nullptr;
InputFn g_windowInput = nullptr;

// Event codes worth logging (their exact meaning is unconfirmed); other event
// values fire far more often and would flood the log.
bool IsInterestingEvent(int event) { return event == 0x1d || event == 0x1e || event == 0x0d; }

int __fastcall MainMenuInputDetour(void* self, void* edx, int event, void* arg3, void* arg4) {
    if (IsInterestingEvent(event)) {
        auto* bytes = static_cast<uint8_t*>(self);
        void* selected = *reinterpret_cast<void**>(bytes + kSelectedOffset);
        int childCount = *reinterpret_cast<int*>(bytes + kChildCountOffset);
        void** children = *reinterpret_cast<void***>(bytes + kChildrenOffset);
        void* child2 = childCount > 2 && children ? children[2] : nullptr;
        void* child3 = childCount > 3 && children ? children[3] : nullptr;
        T3_LOG("menu input event=%X arg3=%p arg4=%p selected=%p childCount=%d child2=%p child3=%p",
               event, arg3, arg4, selected, childCount, child2, child3);
    }
    return g_mainMenuInput(self, edx, event, arg3, arg4);
}

int __fastcall WindowInputDetour(void* self, void* edx, int event, void* arg3, void* arg4) {
    if (IsInterestingEvent(event)) {
        uintptr_t vtable = *reinterpret_cast<uintptr_t*>(self);
        bool isPopup = false;
        for (uintptr_t candidate : kPopupVtables) {
            isPopup |= vtable == candidate;
        }
        if (isPopup) {
            auto* bytes = static_cast<uint8_t*>(self);
            void* selected = *reinterpret_cast<void**>(bytes + kSelectedOffset);
            int childCount = *reinterpret_cast<int*>(bytes + kChildCountOffset);
            T3_LOG("popup input event=%X arg3=%p arg4=%p selected=%p childCount=%d",
                   event, arg3, arg4, selected, childCount);
        }
    }
    return g_windowInput(self, edx, event, arg3, arg4);
}

}  // namespace

bool InstallModdedVersionFormat() {
    static_assert(sizeof(void*) == 4, "T3Main menu patch requires x86");
    const uintptr_t instruction = kFormatOperand - 1;
    if (std::memcmp(reinterpret_cast<const void*>(instruction), kExpectedInstruction,
                    sizeof(kExpectedInstruction)) != 0) {
        T3_LOG("main-menu version marker not installed: callsite bytes changed");
        return false;
    }
    if (*reinterpret_cast<const uintptr_t*>(kFormatOperand) != kOriginalFormat) {
        T3_LOG("main-menu version marker not installed: format operand changed");
        return false;
    }

    DWORD oldProtect = 0;
    void* operand = reinterpret_cast<void*>(kFormatOperand);
    if (!VirtualProtect(operand, sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        T3_LOG("main-menu version marker not installed: VirtualProtect failed (%lu)", GetLastError());
        return false;
    }
    const uintptr_t replacement = reinterpret_cast<uintptr_t>(kModdedFormat);
    std::memcpy(operand, &replacement, sizeof(replacement));
    DWORD ignored = 0;
    const BOOL restored = VirtualProtect(operand, sizeof(uintptr_t), oldProtect, &ignored);
    FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(instruction),
                          sizeof(kExpectedInstruction));
    if (!restored) {
        T3_LOG("main-menu version marker installed, but page protection restore failed (%lu)", GetLastError());
    }
    T3_LOG("main-menu version marker enabled: Modded - T3SDK %s", T3SDK_VERSION);
    return true;
}

bool InstallInputDiagnostics() {
    MH_STATUS status = MH_CreateHook(reinterpret_cast<void*>(kMainMenuInput),
                                     reinterpret_cast<void*>(&MainMenuInputDetour),
                                     reinterpret_cast<void**>(&g_mainMenuInput));
    if (status == MH_OK) {
        status = MH_EnableHook(reinterpret_cast<void*>(kMainMenuInput));
    }
    if (status != MH_OK) {
        T3_LOG("main-menu input diagnostic hook failed: %s", MH_StatusToString(status));
        return false;
    }

    status = MH_CreateHook(reinterpret_cast<void*>(kWindowInput),
                           reinterpret_cast<void*>(&WindowInputDetour),
                           reinterpret_cast<void**>(&g_windowInput));
    if (status == MH_OK) {
        status = MH_EnableHook(reinterpret_cast<void*>(kWindowInput));
    }
    if (status != MH_OK) {
        T3_LOG("popup input diagnostic hook failed: %s", MH_StatusToString(status));
        MH_DisableHook(reinterpret_cast<void*>(kMainMenuInput));
        MH_RemoveHook(reinterpret_cast<void*>(kMainMenuInput));
        g_mainMenuInput = nullptr;
        return false;
    }
    T3_LOG("main-menu/popup input diagnostics enabled");
    return true;
}

}  // namespace t3sdk::menu
