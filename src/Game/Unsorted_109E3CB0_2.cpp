// Game/Unsorted_109E3CB0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class ULevel;

class AAIPathPoint
{
public:
    void FUN_10b06230(int Flags);

    char Unknown00[0x74];
    BITFIELD bLocalGameEvent : 1;
    BITFIELD bTravelGameEvent : 1;
    BITFIELD bDestroyInPainVolume : 1;
    BITFIELD bDontDestroy : 1;
    BITFIELD bHiddenEd : 1;
    BITFIELD bHiddenEdGroup : 1;
    BITFIELD bDirectional : 1;
    BITFIELD bEdShouldSnap : 1;
    BITFIELD bShouldTickInAppTime : 1;
};

// Spawns an actor of Class in Level (its SpawnActor is slot 46); the FRotator H is a rotation rate.
AAIPathPoint* FUN_10a49f00(ULevel* Level, UClass* Class, int C, int D, FVector E, FVector F, FRotator G,
                           FRotator H, bool I);

struct Struct_109E3CB0
{
    ULevel* Unknown00;
};

struct Struct_10AA3520
{
    char Unknown00[0xCC];
    Struct_109E3CB0* UnknownCC;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x109E3CB0 ?FUN_109e3cb0@@YGPAVAAIPathPoint@@PAVUClass@@@Z
AAIPathPoint* __stdcall FUN_109e3cb0(UClass* Class)
{
    AAIPathPoint* Point = FUN_10a49f00(DAT_10f35dec->UnknownCC->Unknown00, Class, 0, 0, FVector(0, 0, 0),
                                       FVector(0, 0, 0), FRotator(0, 0, 0), FRotator(0, 0, 0), false);
    Point->bShouldTickInAppTime = 1;
    Point->FUN_10b06230(0x4000);
    return Point;
}
