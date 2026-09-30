// Game/Class_109421A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

// Member function class structure
struct Class_109421A0
{
    char Unknown00[0xF0];
    int FieldF0;
    char UnknownF4[0x3C];
    void* Field130;

    void FUN_109421a0(int param1, int param2);
};

// FUNCTION: 0x109421A0 ?FUN_109421a0@Class_109421A0@@QAEXHH@Z
void Class_109421A0::FUN_109421a0(int param1, int param2)
{
    if (param1 >= FieldF0)
        return;

    void** ptr = (void**)Field130;
    int index = param1 * 9;
    ptr[index + 1] = (void*)param2;
}
