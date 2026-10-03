// Game/Unsorted_10C64030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern const char DAT_10e9cdec[];

class Class_10C64900_Inner
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual Class_109081E0 Virtual2();
};

struct Struct_10C64900
{
    int Unknown00;
    Class_10C64900_Inner* Unknown04;
};

class Class_10C64900
{
public:
    Class_109081E0 FUN_10c64900();

    char Unknown00[8];
    Struct_10C64900* Unknown08;
};

class Class_10EB7660
{
public:
    Class_10EB7660();

    virtual ~Class_10EB7660();

    int Unknown04;
};

class Class_10C609D0;

// Owns the object FUN_10c60bb0 builds from two vectors; 0x10C60C60 deletes it.
class Class_10C60C60
{
public:
    Class_10C60C60(const FVector& A, const FVector& B);
    ~Class_10C60C60();

    Class_10C609D0* Unknown00;
};

class Class_10C64030_Member
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
    virtual Class_10C64030_Member* Virtual14();
};

struct Struct_10C64030_Param
{
    char Unknown00[8];
    Class_10C64030_Member* Unknown08;
};

class Class_10E9CD84 : public Class_10EB7660
{
public:
    Class_10E9CD84(Struct_10C64030_Param* A);

    virtual ~Class_10E9CD84();

    Class_10C64030_Member* Unknown08;
    Class_10C60C60 Unknown0C;
    int Unknown10;
    bool Unknown14;
    bool Unknown15;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
};

// FUNCTION: 0x10C64030 ??0Class_10E9CD84@@QAE@PAUStruct_10C64030_Param@@@Z
Class_10E9CD84::Class_10E9CD84(Struct_10C64030_Param* A)
    : Unknown0C(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f)), Unknown10(0), Unknown14(false),
      Unknown15(false), Unknown18(0), Unknown1C(-1), Unknown20(0), Unknown24(0), Unknown28(0)
{
    Unknown08 = A->Unknown08->Virtual14();
    A->Unknown08->Virtual13();
}

// FUNCTION: 0x10C648E0 ??_GClass_10E9CD84@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10C64030's definition in this unit.

// FUNCTION: 0x10C64900 ?FUN_10c64900@Class_10C64900@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C64900::FUN_10c64900()
{
    if (Unknown08->Unknown04)
        return Unknown08->Unknown04->Virtual2();
    return Class_109081E0(DAT_10e9cdec);
}
