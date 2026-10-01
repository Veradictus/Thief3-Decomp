// Game/Unsorted_10B88900_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_109B5830
{
public:
    FName FUN_109b5830(int Index);
};

class Class_10B8AB60
{
public:
    FName FUN_10b8ab60();

    char Unknown00[0x30];
    int Unknown30;
    char Unknown34[4];
    Class_109B5830* Unknown38;
};

class Class_10B8AC90;

class Class_10D9B090
{
public:
    void FUN_10d9b090();
};

Class_10D9B090* __stdcall FUN_10d9dcb0(Class_10B8AC90* Obj, int A);

struct Struct_10B8AC90
{
    char Unknown00[0x28];
    unsigned int Unknown28Bits0To4 : 5;
    unsigned int Unknown28Bits5To10 : 6;
    unsigned int Unknown28Bits11To16 : 6;
};

class Class_10B8AC90
{
public:
    void FUN_10b8ac90(int A);

    char Unknown00[0x10];
    Struct_10B8AC90* Unknown10;
};

extern void* DAT_10e89540[];

class Class_10E89AA0
{
public:
    Class_10E89AA0(int A, int B, int C, int D);

    void** Unknown00;
};

class Class_10E89540 : public Class_10E89AA0
{
public:
    Class_10E89540* FUN_10b8b550(int A, int B, int C, int D);

    char Unknown04[0x14];
    bool Unknown18;
    char Unknown19[0x13];
    int Unknown2C;
};

// FUNCTION: 0x10B8AB60 ?FUN_10b8ab60@Class_10B8AB60@@QAE?AVFName@@XZ
FName Class_10B8AB60::FUN_10b8ab60()
{
    if (Unknown30 >= 0)
        return Unknown38->FUN_109b5830(Unknown30);
    return NAME_None;
}

// FUNCTION: 0x10B8AC90 ?FUN_10b8ac90@Class_10B8AC90@@QAEXH@Z
void Class_10B8AC90::FUN_10b8ac90(int A)
{
    if (A != Unknown10->Unknown28Bits11To16)
    {
        FUN_10d9dcb0(this, A)->FUN_10d9b090();
    }
}

// FUNCTION: 0x10B8B550 ?FUN_10b8b550@Class_10E89540@@QAEPAV1@HHHH@Z
Class_10E89540* Class_10E89540::FUN_10b8b550(int A, int B, int C, int D)
{
    this->Class_10E89AA0::Class_10E89AA0(A, B, C, D);
    Unknown00 = DAT_10e89540;
    Unknown2C = 0;
    Unknown18 = true;
    return this;
}
