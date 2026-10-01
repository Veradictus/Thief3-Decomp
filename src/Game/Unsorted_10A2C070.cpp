// Game/Unsorted_10A2C070.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

FVector FUN_10a2c0a0(const FVector* A, const FVector* B);

struct Struct_10A2C350
{
    double Unknown00;
    char Unknown08[0xA8];
};

class Class_10A2C350
{
public:
    void FUN_10a2c350(int A, int B);

    int Unknown00;
    int Unknown04;
    Struct_10A2C350* Unknown08;
};

struct Struct_10A2C500
{
    char Unknown00[0x7D];
    char Unknown7D;
};

class Class_10A2C2F0
{
public:
    int FUN_10a2c2f0(void* A, void* B);
    bool FUN_10a2c500(void* A, void* B);
};

extern int DAT_10f39f30;

void* FUN_10905c10(int Kind, int* Arg, int A, int B, int C, int D);

// FUNCTION: 0x10A2C070 ?FUN_10a2c070@@YAXPAM00@Z
void FUN_10a2c070(float* A, float* B, float* C)
{
    float Z = B[2] + C[2];
    float Y = B[1] + C[1];
    float X = B[0] + C[0];
    A[0] = X;
    A[1] = Y;
    A[2] = Z;
}

// FUNCTION: 0x10A2C0A0 ?FUN_10a2c0a0@@YA?AVFVector@@PBV1@0@Z
FVector FUN_10a2c0a0(const FVector* A, const FVector* B)
{
    return FVector(A->X - B->X, A->Y - B->Y, A->Z - B->Z);
}

// FUNCTION: 0x10A2C350 ?FUN_10a2c350@Class_10A2C350@@QAEXHH@Z
void Class_10A2C350::FUN_10a2c350(int A, int B)
{
    Struct_10A2C350 Temp = Unknown08[A];
    Unknown08[A] = Unknown08[B];
    Unknown08[B] = Temp;
}

// FUNCTION: 0x10A2C500 ?FUN_10a2c500@Class_10A2C2F0@@QAE_NPAX0@Z
bool Class_10A2C2F0::FUN_10a2c500(void* A, void* B)
{
    Struct_10A2C500* Entry = (Struct_10A2C500*)FUN_10a2c2f0(A, B);
    if (Entry && !Entry->Unknown7D)
        return true;
    return false;
}

// FUNCTION: 0x10A2DE50 ?FUN_10a2de50@@YAXXZ
void FUN_10a2de50()
{
    int Handle = DAT_10f39f30;
    if (Handle == 0)
    {
        int Value = Handle;
        DAT_10f39f30 = (int)FUN_10905c10(1, &Value, Handle, Handle, Handle, Handle);
    }
}
