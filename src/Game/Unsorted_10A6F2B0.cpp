// Game/Unsorted_10A6F2B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

class Class_10E6BA88
{
public:
    Class_10E6BA88();

    virtual ~Class_10E6BA88();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10A6FED0_Member
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
    virtual void Virtual13(int A);
};

struct Struct_10A6FED0
{
    char Unknown00[0xB0];
    Class_10A6FED0_Member* UnknownB0;
};

class Class_10A6FED0_Owner
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Struct_10A6FED0* A, int B, int C);
};

struct Struct_10AA3520
{
    char Unknown00[0x1C];
    Class_10A6FED0_Owner* Unknown1C;
};

extern Struct_10AA3520* DAT_10f35dec;

extern int DAT_10e6b594;

struct Struct_10AB0400
{
};

class Class_10AB0400
{
public:
    void FUN_10a6e990();
    void FUN_10ab0400()
    {
        FUN_10a6e990();
        delete Unknown04;
        Unknown04 = 0;
    }

    char Unknown00[4];
    Struct_10AB0400* Unknown04;
};

class Class_10A6F9B0
{
public:
    void FUN_10a6f9b0();

    void* Field00;
    char Unknown04[4];
    Class_10AB0400 Unknown08;
    char Unknown10[4];
    std::vector<void*> Unknown14;
};

// FUNCTION: 0x10A6F9B0 ?FUN_10a6f9b0@Class_10A6F9B0@@QAEXXZ
void Class_10A6F9B0::FUN_10a6f9b0()
{
    Unknown14.~vector();
    Unknown08.FUN_10ab0400();
    Field00 = (void*)&DAT_10e6b594;
}

// FUNCTION: 0x10A6FED0 ?FUN_10a6fed0@@YGXPAUStruct_10A6FED0@@H@Z
void __stdcall FUN_10a6fed0(Struct_10A6FED0* Obj, int B)
{
    Class_10A6FED0_Member* Child = Obj->UnknownB0;
    if (Child)
        Child->Virtual13(1);
    DAT_10f35dec->Unknown1C->Virtual1(Obj, 0, 0);
}

// FUNCTION: 0x10A70BC0 ??0Class_10E6BA88@@QAE@XZ
Class_10E6BA88::Class_10E6BA88()
{
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
}

// FUNCTION: 0x10A70C90 ??_GClass_10E6BA88@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10A70BC0's definition in this unit.
