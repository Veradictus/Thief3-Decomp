// Game/Unsorted_10B3ADD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10B21820_Object
{
    char Unknown00[0x4A4];
    FVector Unknown4A4;
};

class Class_10B21820
{
public:
    Struct_10B21820_Object* FUN_10991e10();
};

class Class_10E7E538
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
    virtual void Virtual13();
    virtual float FUN_10b3af10(Class_10B21820* Obj);
};

struct Struct_10B48890;

class Class_10B3AF40_UnknownB0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Struct_10B48890* Virtual6();
};

struct Struct_10B3AF40_Param
{
    char Unknown00[0xB0];
    Class_10B3AF40_UnknownB0* UnknownB0;
};

// FUNCTION: 0x10B3AF10 ?FUN_10b3af10@Class_10E7E538@@UAEMPAVClass_10B21820@@@Z
float Class_10E7E538::FUN_10b3af10(Class_10B21820* Obj)
{
    FVector Location = Obj->FUN_10991e10()->Unknown4A4;
    return Location.Z;
}

// FUNCTION: 0x10B3AF40 ?FUN_10b3af40@@YGPAUStruct_10B48890@@PAUStruct_10B3AF40_Param@@@Z
Struct_10B48890* __stdcall FUN_10b3af40(Struct_10B3AF40_Param* p1)
{
    return p1->UnknownB0->Virtual6();
}
