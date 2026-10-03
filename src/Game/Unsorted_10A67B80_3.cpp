// Game/Unsorted_10A67B80_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

struct Struct_10AA3520
{
    char Unknown00[8];
    UObject* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10A67C40 ?FUN_10a67c40@@YANXZ
double FUN_10a67c40()
{
    UObject* Obj = DAT_10f35dec->Unknown08;
    if (Obj)
        return Cast<APlayerPawn>(Obj)->SimtimePlayedTimer;
    return 0.0;
}
