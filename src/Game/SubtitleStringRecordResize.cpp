// Game/SubtitleStringRecordResize.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cString.h"
#include "Game/Class_10B2AB30.h"

struct SubtitleStringRecord
{
    cString Text;
    char Unknown04[8];
};

// FUNCTION: 0x10B2A8A0 ?FUN_10b2a8a0@Class_10B2AB30@@QAEXH@Z
void Class_10B2AB30::FUN_10b2a8a0(int Count)
{
    int OldCount = Unknown00;
    int Capacity = !Unknown08 ? 0 : Unknown04 / sizeof(SubtitleStringRecord);
    for (int I = Count; I < OldCount; ++I)
        ((SubtitleStringRecord*)Unknown08)[I].Text.Class_1090A780::~Class_1090A780();
    GetAllocator()->Virtual8(0, 0);
    if (Count > Capacity)
    {
        int NewCapacity = Count;
        if (Capacity)
            NewCapacity = (Count & ~15) + 16;
        Unknown08 = GetAllocator()->Virtual3(Unknown08, NewCapacity * sizeof(SubtitleStringRecord), 0, 0, 0, 0);
        Unknown04 = NewCapacity * sizeof(SubtitleStringRecord);
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
            Unknown08 = GetAllocator()->Virtual3(Unknown08, NewCapacity * sizeof(SubtitleStringRecord), 0, 0, 0, 0);
            Unknown04 = NewCapacity * sizeof(SubtitleStringRecord);
        }
    }
    for (int I = OldCount; I < Count; ++I)
    {
        SubtitleStringRecord* Item = (SubtitleStringRecord*)Unknown08 + I;
        if (Item)
            Item->Text.Unknown00 = 0;
    }
    GetAllocator()->Virtual9();
    Unknown00 = Count;
}
