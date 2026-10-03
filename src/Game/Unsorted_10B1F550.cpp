// Game/Unsorted_10B1F550.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10991FF0
{
public:
    float FUN_10991ff0();
};

bool FUN_10b1fc30(Class_10991FF0* Actor, const FVector& Offset);

bool FUN_10b21010(Class_10991FF0* Actor);

// FUNCTION: 0x10B21010 ?FUN_10b21010@@YA_NPAVClass_10991FF0@@@Z
bool FUN_10b21010(Class_10991FF0* Actor)
{
    float Z = Actor->FUN_10991ff0() - 48.0f;
    if (FUN_10b1fc30(Actor, FVector(0.0f, 0.0f, Z)))
        return true;
    if (FUN_10b1fc30(Actor, FVector(0.0f, 0.0f, Z + 5.0f)))
        return true;
    if (FUN_10b1fc30(Actor, FVector(0.0f, 0.0f, Z - 5.0f)))
        return true;
    return false;
}
