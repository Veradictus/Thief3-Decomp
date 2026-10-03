// Game/Unsorted_10ABF100.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10974340
{
public:
    int FUN_10974340();
};

class UEngine
{
public:
    char Unknown00[0x10C];
    Class_10974340* Unknown10C;
};

extern UEngine* GEngine;

struct Struct_10974340_Result
{
    char Unknown00[0x218];
    unsigned int Unknown218;
};

class Class_10ABF100
{
public:
    bool FUN_10abf100();
};

struct Struct_10ABF1B0
{
    char Unknown00[4];
    int Unknown04;
    char Unknown08[0x2C];
};

class APlayerPawn
{
public:
    char Unknown00[0x214];
    TArray<Struct_10ABF1B0> CitySectionGoals;
};

struct Struct_10AA3520
{
    char Unknown00[8];
    APlayerPawn* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10ABF100 ?FUN_10abf100@Class_10ABF100@@QAE_NXZ
bool Class_10ABF100::FUN_10abf100()
{
    UEngine* Engine = GEngine;
    if (Engine && Engine->Unknown10C && Engine->Unknown10C->FUN_10974340())
        return (((Struct_10974340_Result*)Engine->Unknown10C->FUN_10974340())->Unknown218 & 0x100) == 0x100;
    return false;
}

// FUNCTION: 0x10ABF1B0 ?FUN_10abf1b0@@YGPAUStruct_10ABF1B0@@H@Z
Struct_10ABF1B0* __stdcall FUN_10abf1b0(int A)
{
    APlayerPawn* Pawn = DAT_10f35dec->Unknown08;
    for (int i = 0; i < Pawn->CitySectionGoals.Num(); i++)
    {
        if (A == Pawn->CitySectionGoals(i).Unknown04)
            return &Pawn->CitySectionGoals(i);
    }
    return 0;
}
