// Game/WindowManager.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

// The UI layout manager (GWindowManager, docs/engine.md "UI windows"): the layout size
// is [WindowManager] AssumedUIScreenWidth / AssumedUIScreenHeight.
class WindowManager
{
public:
    char Unknown00[0xCC];
    float AssumedUIScreenWidth;
    float AssumedUIScreenHeight;

    void GetUIScreenSize(FVector* Out);
};

// FUNCTION: 0x109E47E0 ?GetUIScreenSize@WindowManager@@QAEXPAVFVector@@@Z
void WindowManager::GetUIScreenSize(FVector* Out)
{
    Out->X = AssumedUIScreenWidth;
    Out->Y = AssumedUIScreenHeight;
}
