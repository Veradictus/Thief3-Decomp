// Game/Unsorted_1091E240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_1091E290
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

class Class_1091E290
{
public:
    void FUN_1091e290(const Struct_1091E290& A);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
};

// Nine floats, built from the nine values it is given.
class Struct_1091E240
{
public:
    Struct_1091E240(float A, float B, float C, float D, float E, float F, float G, float H, float I)
        : M00(A), M01(B), M02(C), M10(D), M11(E), M12(F), M20(G), M21(H), M22(I) {}

    float M00, M01, M02;
    float M10, M11, M12;
    float M20, M21, M22;
};

class Class_1091E240
{
public:
    Struct_1091E240 FUN_1091e240();

    FVector Unknown00;
    char Unknown0C[4];
    FVector Unknown10;
    char Unknown1C[4];
    FVector Unknown20;
    char Unknown2C[4];
};

// FUNCTION: 0x1091E240 ?FUN_1091e240@Class_1091E240@@QAE?AVStruct_1091E240@@XZ
Struct_1091E240 Class_1091E240::FUN_1091e240()
{
    return Struct_1091E240(Unknown00.X, Unknown00.Y, Unknown00.Z,
                           Unknown10.X, Unknown10.Y, Unknown10.Z,
                           Unknown20.X, Unknown20.Y, Unknown20.Z);
}

// FUNCTION: 0x1091E290 ?FUN_1091e290@Class_1091E290@@QAEXABUStruct_1091E290@@@Z
void Class_1091E290::FUN_1091e290(const Struct_1091E290& A)
{
    Unknown00 = A.Unknown00;
    Unknown04 = A.Unknown04;
    Unknown08 = A.Unknown08;
    Unknown0C = 0;
    Unknown10 = A.Unknown0C;
    Unknown14 = A.Unknown10;
    Unknown18 = A.Unknown14;
    Unknown1C = 0;
    Unknown20 = A.Unknown18;
    Unknown24 = A.Unknown1C;
    Unknown28 = A.Unknown20;
    Unknown2C = 0;
}
