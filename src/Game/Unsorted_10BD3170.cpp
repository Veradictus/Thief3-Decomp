// Game/Unsorted_10BD3170.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    virtual void Virtual0();
};

class Class_10E93710 : public Class_10E90D70
{
public:
    Class_10E93710(int A, int B);
};

class Class_10E93878 : public Class_10E93710
{
public:
    Class_10E93878(int A, int B);
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10BD4120
{
public:
    void FUN_10a20940(int Count);
    void FUN_10bd4120();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10BD3830_Owner
{
    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

struct Struct_10BD3830_Target
{
    char Unknown00[0x2C];
    FVector Unknown2C;
};

class Object_10BD3830
{
public:
    virtual void Virtual0();
    virtual unsigned char Virtual1(FVector* A, int* B);
};

class Class_10BD3830
{
public:
    int FUN_10bd2340(int A, const FVector& B, const FVector& C, int D, int E);
    int FUN_10bd3830(int A, Object_10BD3830* Obj, int C, int D);

    char Unknown00[4];
    Struct_10BD3830_Owner* Unknown04;
};

// FUNCTION: 0x10BD3830 ?FUN_10bd3830@Class_10BD3830@@QAEHHPAVObject_10BD3830@@HH@Z
int Class_10BD3830::FUN_10bd3830(int A, Object_10BD3830* Obj, int C, int D)
{
    FVector Vec(0.0f, 0.0f, 0.0f);
    int Count = 0;
    if (Obj && Obj->Virtual1(&Vec, &Count) == 1)
    {
        Struct_10BD3830_Target* Target = (Struct_10BD3830_Target*)Unknown04->Unknown08->FUN_10c7d570();
        return FUN_10bd2340(A, Vec, Vec - Target->Unknown2C, C, D);
    }
    return 0;
}

// FUNCTION: 0x10BD4120 ?FUN_10bd4120@Class_10BD4120@@QAEXXZ
void Class_10BD4120::FUN_10bd4120()
{
    FUN_10a20940(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10BD51C0 ??0Class_10E93878@@QAE@HH@Z
Class_10E93878::Class_10E93878(int A, int B) : Class_10E93710(A, B)
{
}
