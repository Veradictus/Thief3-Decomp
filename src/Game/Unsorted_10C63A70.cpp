// Game/Unsorted_10C63A70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C63AD0_Member {
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
    virtual void F6() = 0;
    virtual void F7() = 0;
};

class Class_10C63AD0 {
public:
    char Unknown00[8];
    Class_10C63AD0_Member* Unknown08;
    void FUN_10c63ad0();
};

class Class_10C63AB0;

class Class_10C63AB0_Member
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
    virtual void Virtual10(int p1, Class_10C63AB0* p2);
};

class Class_10C63AB0
{
public:
    void FUN_10c63ab0(int p1);

    char Unknown00[8];
    Class_10C63AB0_Member* Unknown08;
};

struct Struct_10B21820_Object
{
    void FUN_109bdf20();
};

class Class_10990E20
{
public:
    bool FUN_10990e20();
};

class Class_10B21820 : public Class_10990E20
{
public:
    Struct_10B21820_Object* FUN_10991e10();
};

class Class_10C63A70;

class Class_10C63A70_Unknown08
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
    virtual void Virtual9(Class_10C63A70* A, int B);
};

class Class_10C63A70
{
public:
    void FUN_10c63a70();

    char Unknown00[8];
    Class_10C63A70_Unknown08* Unknown08;
    char Unknown0C[0xC];
    Class_10B21820* Unknown18;
};

// FUNCTION: 0x10C63A70 ?FUN_10c63a70@Class_10C63A70@@QAEXXZ
void Class_10C63A70::FUN_10c63a70()
{
    Unknown08->Virtual9(this, 1);
    if (Unknown18 && Unknown18->FUN_10990e20())
    {
        Struct_10B21820_Object* Obj = Unknown18->FUN_10991e10();
        if (Obj)
            Obj->FUN_109bdf20();
    }
}

// FUNCTION: 0x10C63AB0 ?FUN_10c63ab0@Class_10C63AB0@@QAEXH@Z
void Class_10C63AB0::FUN_10c63ab0(int p1)
{
    Unknown08->Virtual10(p1, this);
}

// FUNCTION: 0x10C63AD0 ?FUN_10c63ad0@Class_10C63AD0@@QAEXXZ
void Class_10C63AD0::FUN_10c63ad0()
{
    Unknown08->F7();
}
