// Game/Unsorted_10B1DC70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

// The vector flattened onto the ground plane and normalized.
inline FVector FlatNormal(const FVector& V)
{
    FVector Result = V;
    Result.Z = 0.0f;
    Result.Normalize();
    return Result;
}

struct Struct_10B1DD70_Param;

FVector FUN_10b1dd70(Struct_10B1DD70_Param* A);

struct Struct_10B1DEB0_Param;

FVector FUN_10b1deb0(Struct_10B1DEB0_Param* A);

struct Struct_10B1E010_Param;

FVector FUN_10b1e010(Struct_10B1E010_Param* A);

struct Struct_10B1DCA0_Param;

struct Struct_10B1DCA0
{
    Struct_10B1DCA0() {}

    FVector Unknown00;
    FVector Unknown0C;
    FVector Unknown18;
    FVector Unknown24;
};

Struct_10B1DCA0 FUN_10b1dca0(Struct_10B1DCA0_Param* p1);

void FUN_109672e0(const Struct_10B1DCA0& Coords, const FVector& V, FVector& Out);

FVector FUN_10b1f490(Struct_10B1DCA0_Param* A);

class Class_10A18FA0
{
public:
    bool FUN_10a18fa0(int Index);
};

class Object_10A18FC0 : public Class_10A18FA0
{
};

Object_10A18FC0* FUN_10a18fc0();

// FUNCTION: 0x10B1DC70 ?FUN_10b1dc70@@YA_NXZ
bool FUN_10b1dc70()
{
    return FUN_10a18fc0()->FUN_10a18fa0(6) || FUN_10a18fc0()->FUN_10a18fa0(5);
}

// FUNCTION: 0x10B1DE50 ?FUN_10b1de50@@YA?AVFVector@@PAUStruct_10B1DD70_Param@@@Z
FVector FUN_10b1de50(Struct_10B1DD70_Param* A)
{
    return FlatNormal(FUN_10b1dd70(A));
}

// FUNCTION: 0x10B1DFB0 ?FUN_10b1dfb0@@YA?AVFVector@@PAUStruct_10B1DEB0_Param@@@Z
FVector FUN_10b1dfb0(Struct_10B1DEB0_Param* A)
{
    return FlatNormal(FUN_10b1deb0(A));
}

// FUNCTION: 0x10B1E0F0 ?FUN_10b1e0f0@@YA?AVFVector@@PAUStruct_10B1E010_Param@@@Z
FVector FUN_10b1e0f0(Struct_10B1E010_Param* A)
{
    return FlatNormal(FUN_10b1e010(A));
}

// FUNCTION: 0x10B1F490 ?FUN_10b1f490@@YA?AVFVector@@PAUStruct_10B1DCA0_Param@@@Z
FVector FUN_10b1f490(Struct_10B1DCA0_Param* p1)
{
    Struct_10B1DCA0 Coords = FUN_10b1dca0(p1);
    FVector Result;
    FVector V(1.0f, 0.0f, 0.0f);
    FUN_109672e0(Coords, V, Result);
    return Result;
}

// FUNCTION: 0x10B1F4F0 ?FUN_10b1f4f0@@YA?AVFVector@@PAUStruct_10B1DCA0_Param@@@Z
FVector FUN_10b1f4f0(Struct_10B1DCA0_Param* A)
{
    return FlatNormal(FUN_10b1f490(A));
}
