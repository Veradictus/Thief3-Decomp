// Game/LockPickPinSelection.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10AD0200.h"

class Class_1098E3D0;

class Class_10B3F830_Arg
{
public:
    char Unknown00[0x458];
    Class_1098E3D0* Unknown458;
};

class Class_10ACF3A0
{
public:
    void FUN_10acfb10(int Actor, void* Out);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0xFC];
    Class_10ACF3A0* UnknownFC;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class cLockPickController
{
public:
    void FUN_10b3f070(Class_10B3F830_Arg* A);
    int FUN_10b3e620(float* Position);
    char Unknown00[0x18];
    FVector* PinPositions;
    FVector Target;
    char Unknown28[0xC];
    int Direction;
    char Unknown38[0x34];
    float Cooldown;
    char Unknown70[4];
    int CurrentPin;
};

T3_CHECK_SIZE(Class_10AD0200, 16);

// FUNCTION: 0x10B3F070 ?FUN_10b3f070@cLockPickController@@QAEXPAVClass_10B3F830_Arg@@@Z
void cLockPickController::FUN_10b3f070(Class_10B3F830_Arg* A)
{
    Class_10AD0200 Info;
    DAT_10f3a3d8->UnknownFC->FUN_10acfb10((int)A->Unknown458, &Info);
    CurrentPin = Info.Unknown0C;
    Target = PinPositions[CurrentPin];
    Direction = FUN_10b3e620(&Target.X);
    Cooldown = 2.0f;
}
