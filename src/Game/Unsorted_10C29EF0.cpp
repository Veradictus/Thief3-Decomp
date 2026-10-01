// Game/Unsorted_10C29EF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern void* DAT_10e9aa20[];

class Class_10E9AA20
{
public:
    Class_10E9AA20* FUN_10c2e350(int p1);

    void** VTable;
    int Unknown04;
};

extern void* DAT_10e9aa2c[];

class Class_10E9AA2C
{
public:
    Class_10E9AA2C* FUN_10c2e370(int p1);

    void** VTable;
    int Unknown04;
};

class Class_10AF3AA0
{
public:
    void FUN_10af3aa0(const char* Format, ...);
};

// FUNCTION: 0x10C2A290 ?FUN_10c2a290@@YAXPAVClass_10AF3AA0@@PBD@Z
void FUN_10c2a290(Class_10AF3AA0* Log, const char* Format)
{
    if (Log)
        Log->FUN_10af3aa0(Format);
}

// FUNCTION: 0x10C2A2B0 ?FUN_10c2a2b0@@YAXPAVFOutputDevice@@W4EName@@PBD@Z
void FUN_10c2a2b0(FOutputDevice* Out, EName Event, const ANSICHAR* Fmt)
{
    if (Out)
        Out->Logf(Event, Fmt);
}

// FUNCTION: 0x10C2E350 ?FUN_10c2e350@Class_10E9AA20@@QAEPAV1@H@Z
Class_10E9AA20* Class_10E9AA20::FUN_10c2e350(int p1)
{
    VTable = DAT_10e9aa20;
    Unknown04 = p1;
    return this;
}

// FUNCTION: 0x10C2E370 ?FUN_10c2e370@Class_10E9AA2C@@QAEPAV1@H@Z
Class_10E9AA2C* Class_10E9AA2C::FUN_10c2e370(int p1)
{
    VTable = DAT_10e9aa2c;
    Unknown04 = p1;
    return this;
}
