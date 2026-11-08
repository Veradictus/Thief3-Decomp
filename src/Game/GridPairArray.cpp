// Game/GridPairArray.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <new>
#include "Game/Class_10C223A0.h"
#include "Game/Class_10905A90_Member.h"

Class_10905A90_Member* GetAllocator();

struct GridPair
{
    int First;
    int Last;
    GridPair() : First(-1), Last(-1) {}
};

// FUNCTION: 0x10C20C70 ?FUN_10c20c70@Class_10C223A0@@QAEXH@Z
void Class_10C223A0::FUN_10c20c70(int NewCount)
{
    int OldCount = Unknown00;
    int Capacity = !Unknown08 ? 0 : Unknown04 / sizeof(GridPair);
    GetAllocator()->Virtual8(0, 0);
    if (NewCount > Capacity)
    {
        int NewCapacity = NewCount;
        if (Capacity)
            NewCapacity = (NewCount & ~15) + 16;
        Unknown08 = GetAllocator()->Virtual3(Unknown08, NewCapacity * sizeof(GridPair), 0, 0, 0, 0);
        Unknown04 = NewCapacity * sizeof(GridPair);
    }
    else if (NewCount <= Capacity - 16)
    {
        if (NewCount == 0)
        {
            GetAllocator()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
        else
        {
            int NewCapacity = (NewCount & ~15) + 16;
            Unknown08 = GetAllocator()->Virtual3(Unknown08, NewCapacity * sizeof(GridPair), 0, 0, 0, 0);
            Unknown04 = NewCapacity * sizeof(GridPair);
        }
    }
    for (int i = OldCount; i < NewCount; ++i)
        new (&((GridPair*)Unknown08)[i]) GridPair;
    GetAllocator()->Virtual9();
    Unknown00 = NewCount;
}
