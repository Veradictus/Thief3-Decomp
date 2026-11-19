// Game/TriggerStringArrayResize.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string.h>
#include "Game/cString.h"
#include "Game/Class_10A81D20.h"

// FUNCTION: 0x10A80E90 ?FUN_10a80e90@Class_10A81D20@@QAEXH@Z
void Class_10A81D20::FUN_10a80e90(int Count)
{
    int OldCount = Unknown00;
    int Capacity = !Unknown08 ? 0 : Unknown04 / sizeof(cString);
    for (int I = Count; I < OldCount; ++I)
        ((cString*)Unknown08)[I].Class_1090A780::~Class_1090A780();
    GetAllocator()->Virtual8(0, 0);
    if (Count > Capacity)
    {
        int NewCapacity = Count;
        if (Capacity)
            NewCapacity = (Count & ~15) + 16;
        Unknown08 = GetAllocator()->Virtual3(Unknown08, NewCapacity * sizeof(cString), 0, 0, 0, 0);
        Unknown04 = NewCapacity * sizeof(cString);
        memset((cString*)Unknown08 + Capacity, 0, (NewCapacity - Capacity) * sizeof(cString));
    }
    else if (Count <= Capacity - 16)
    {
        if (Count == 0)
        {
            GetAllocator()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
        else
        {
            int NewCapacity = (Count & ~15) + 16;
            Unknown08 = GetAllocator()->Virtual3(Unknown08, NewCapacity * sizeof(cString), 0, 0, 0, 0);
            Unknown04 = NewCapacity * sizeof(cString);
        }
    }
    for (int I = OldCount; I < Count; ++I)
    {
        cString* Item = (cString*)Unknown08 + I;
        if (Item)
            Item->Unknown00 = 0;
    }
    GetAllocator()->Virtual9();
    Unknown00 = Count;
}
