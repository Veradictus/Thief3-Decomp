// Game/WindowManager_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class WindowManager
{
public:
    char Unknown00[0xCC];
    float AssumedUIScreenWidth;
    float AssumedUIScreenHeight;

    FVector FUN_109e4290(int X, int Y);
};

// FUNCTION: 0x109E4290 ?FUN_109e4290@WindowManager@@QAE?AVFVector@@HH@Z
FVector WindowManager::FUN_109e4290(int X, int Y)
{
    FVector Result;
    Result.X = X / (AssumedUIScreenWidth * 0.5f) - 1.0f;
    Result.Y = 1.0f - Y / (AssumedUIScreenHeight * 0.5f);
    Result.Z = 0.0f;
    return Result;
}
