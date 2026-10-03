// Game/Unsorted_10A67B80_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

struct Struct_10AA3520
{
    char Unknown00[8];
    UObject* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10A67CA0
{
public:
    void FUN_10a67ca0();
};

// FUNCTION: 0x10A67CA0 ?FUN_10a67ca0@Class_10A67CA0@@QAEXXZ
void Class_10A67CA0::FUN_10a67ca0()
{
    UObject* Obj = DAT_10f35dec->Unknown08;
    if (Obj)
        Cast<APlayerPawn>(Obj)->SimtimePlayedTimer = 0.0f;
}
