// Game/Unsorted_10ABC0B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10ABC0B0_Info
{
    int Unknown00;
    int Unknown04;
    BYTE Unknown08;
};

struct Struct_10ABC0B0
{
    Struct_10ABC0B0(const Struct_10ABC0B0_Info& Info, const FVector& InUnknown04, const FVector& InUnknown10)
        : Unknown00(Info.Unknown04), Unknown04(InUnknown04), Unknown10(InUnknown10), Unknown1C(Info.Unknown08),
          Unknown1D(0), Unknown20(-1)
    {
    }

    int Unknown00;
    FVector Unknown04;
    FVector Unknown10;
    BYTE Unknown1C;
    BYTE Unknown1D;
    int Unknown20;
};

// FUNCTION: 0x10ABC0B0 ?FUN_10abc0b0@@YA?AUStruct_10ABC0B0@@ABVFVector@@0ABUStruct_10ABC0B0_Info@@@Z
Struct_10ABC0B0 FUN_10abc0b0(const FVector& A, const FVector& B, const Struct_10ABC0B0_Info& Info)
{
    return Struct_10ABC0B0(Info, B, A);
}
