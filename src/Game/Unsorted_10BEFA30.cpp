// Game/Unsorted_10BEFA30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10BEFA30
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BEFA30
{
public:
    Class_10BEFA30* FUN_10befa30(const Class_10BEFA30& A);

    char Unknown00[4];
    Struct_10BEFA30 Unknown04;
    int Unknown10;
    int Unknown14;
    unsigned char Unknown18;
    int Unknown1C;
    int Unknown20;
};

float appFrand();

double FUN_10c00480();

class Class_10BEFA80
{
public:
    void FUN_10befa80();

    char Unknown00[0x224];
    float Unknown224;
};

class Class_10BF0360
{
public:
    float FUN_10bef550();
    void FUN_10bf0360(FVector A, float B);

    char Unknown00[0x114];
    int Unknown114;
    int Unknown118;
    float Unknown11C;
    char Unknown120[0xB0];
    FVector Unknown1D0;
    float Unknown1DC;
};

class Class_10BC4160
{
public:
    char Unknown00[8];

    int FUN_10bc4160();
};

class Class_10AAF570
{
public:
    int FUN_10aaf570();
};

class Class_10BF03B0_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13(int A, void* B, int C, int D);
};

class Class_10BF03B0 : public Class_10BC4160
{
public:
    void FUN_10bf03b0();

    char Unknown08[0x78];
    char Unknown80;
};

class Class_10BF03E0 : public Class_10BC4160
{
public:
    void FUN_10bf03e0();

    char Unknown08[0x78];
    char Unknown80;
};

class Class_10BAC050
{
public:
    int FUN_10baac90(int A);
};

class Object_10BF0A30
{
public:
    char Unknown00[8];
    Class_10BAC050* Unknown08;
};

class Class_10BF0A30
{
public:
    bool FUN_10bf0a30(int A);

    char Unknown00[4];
    Object_10BF0A30* Unknown04;
};

// FUNCTION: 0x10BEFA30 ?FUN_10befa30@Class_10BEFA30@@QAEPAV1@ABV1@@Z
Class_10BEFA30* Class_10BEFA30::FUN_10befa30(const Class_10BEFA30& A)
{
    Unknown04 = A.Unknown04;
    Unknown10 = A.Unknown10;
    Unknown14 = A.Unknown14;
    Unknown18 = A.Unknown18;
    Unknown1C = A.Unknown1C;
    Unknown20 = A.Unknown20;
    return this;
}

// FUNCTION: 0x10BEFA80 ?FUN_10befa80@Class_10BEFA80@@QAEXXZ
void Class_10BEFA80::FUN_10befa80()
{
    float Delay = appFrand();
    Delay *= 3.0f;
    Delay += 3.0f;
    Unknown224 = Delay + FUN_10c00480();
}

// FUNCTION: 0x10BF0360 ?FUN_10bf0360@Class_10BF0360@@QAEXVFVector@@M@Z
void Class_10BF0360::FUN_10bf0360(FVector A, float B)
{
    Unknown1D0 = A;
    Unknown1DC = B;
    Unknown118 = 2;
    Unknown11C = FUN_10bef550();
    Unknown114 = 3;
}

// FUNCTION: 0x10BF03B0 ?FUN_10bf03b0@Class_10BF03B0@@QAEXXZ
void Class_10BF03B0::FUN_10bf03b0()
{
    Class_10AAF570* A = (Class_10AAF570*)FUN_10bc4160();
    Class_10BF03B0_Member* B = (Class_10BF03B0_Member*)A->FUN_10aaf570();
    B->Virtual13(0x29, &Unknown80, 0, 1);
}

// FUNCTION: 0x10BF03E0 ?FUN_10bf03e0@Class_10BF03E0@@QAEXXZ
void Class_10BF03E0::FUN_10bf03e0()
{
    Class_10AAF570* A = (Class_10AAF570*)FUN_10bc4160();
    Class_10BF03B0_Member* B = (Class_10BF03B0_Member*)A->FUN_10aaf570();
    B->Virtual13(0x2a, &Unknown80, 0, 1);
}

// FUNCTION: 0x10BF0A30 ?FUN_10bf0a30@Class_10BF0A30@@QAE_NH@Z
bool Class_10BF0A30::FUN_10bf0a30(int A)
{
    if (A != 0)
    {
        Class_10BAC050* Obj = Unknown04->Unknown08;
        if (Obj->FUN_10baac90(A) != 0)
            return true;
    }
    return false;
}
