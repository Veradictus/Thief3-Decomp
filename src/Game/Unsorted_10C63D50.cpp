// Game/Unsorted_10C63D50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10c63d50_Member
{
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
};

class Class_10c63d50
{
public:
    char Unknown00[8];
    Class_10c63d50_Member* Unknown08;
    void FUN_10c63d50();
};

class Class_10c63d60_Member
{
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
    virtual void F6() = 0;
    virtual void F7() = 0;
    virtual void F8() = 0;
    virtual void F9() = 0;
    virtual void FA() = 0;
    virtual void FB() = 0;
    virtual void FC() = 0;
    virtual void FD() = 0;
    virtual void FE() = 0;
    virtual void FF() = 0;
    virtual void F10() = 0;
    virtual void F11() = 0;
    virtual void F12() = 0;
    virtual void F13() = 0;
    virtual void F14() = 0;
    virtual void F15() = 0;
    virtual void F16() = 0;
    virtual void F17() = 0;
    virtual void F18() = 0;
    virtual void F19() = 0;
    virtual void F1A() = 0;
};

class Class_10c63d60
{
public:
    char Unknown00[8];
    Class_10c63d60_Member* Unknown08;
    void FUN_10c63d60();
};

class Class_10c63d70_Member
{
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
    virtual void F6() = 0;
    virtual void F7() = 0;
    virtual void F8() = 0;
    virtual void F9() = 0;
    virtual void FA() = 0;
    virtual void FB() = 0;
    virtual void FC() = 0;
    virtual void FD() = 0;
    virtual void FE() = 0;
    virtual void FF() = 0;
    virtual void F10() = 0;
    virtual void F11() = 0;
    virtual void F12() = 0;
};

class Class_10c63d70
{
public:
    char Unknown00[8];
    Class_10c63d70_Member* Unknown08;
    void FUN_10c63d70();
};

extern float DAT_10f06a78;

extern float DAT_10e7a734;

extern float DAT_10f06a7c;

class Class_10c63dc0_Member
{
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
    virtual void F6() = 0;
    virtual void F7() = 0;
    virtual void F8() = 0;
    virtual void F9() = 0;
    virtual void FA() = 0;
    virtual void FB() = 0;
    virtual void FC() = 0;
    virtual void FD() = 0;
    virtual void FE() = 0;
    virtual void FF() = 0;
    virtual void F10() = 0;
    virtual void F11() = 0;
    virtual void F12() = 0;
    virtual void F13() = 0;
    virtual void F14() = 0;
    virtual void F15() = 0;
    virtual void F16() = 0;
    virtual void F17() = 0;
    virtual void F18() = 0;
};

class Class_10c63dc0
{
public:
    char Unknown00[8];
    Class_10c63dc0_Member* Unknown08;
    void FUN_10c63dc0();
};

struct Struct_10C63DD0
{
    char Unknown00[0x20];
    char Unknown20;
};

class Class_10C63DD0
{
public:
    int FUN_10c63dd0(int A);

    char Unknown00[8];
    Struct_10C63DD0* Unknown08;
    char Unknown0C[4];
    int Unknown10;
};

// FUNCTION: 0x10C63D50 ?FUN_10c63d50@Class_10c63d50@@QAEXXZ
void Class_10c63d50::FUN_10c63d50()
{
    Unknown08->F1();
}

// FUNCTION: 0x10C63D60 ?FUN_10c63d60@Class_10c63d60@@QAEXXZ
void Class_10c63d60::FUN_10c63d60()
{
    Unknown08->F1A();
}

// FUNCTION: 0x10C63D70 ?FUN_10c63d70@Class_10c63d70@@QAEXXZ
void Class_10c63d70::FUN_10c63d70()
{
    Unknown08->F12();
}

// FUNCTION: 0x10C63D80 ?FUN_10c63d80@@YAMXZ
float FUN_10c63d80()
{
    return DAT_10f06a78 - DAT_10e7a734 + DAT_10f06a7c;
}

// FUNCTION: 0x10C63DC0 ?FUN_10c63dc0@Class_10c63dc0@@QAEXXZ
void Class_10c63dc0::FUN_10c63dc0()
{
    Unknown08->F18();
}

// FUNCTION: 0x10C63DD0 ?FUN_10c63dd0@Class_10C63DD0@@QAEHH@Z
int Class_10C63DD0::FUN_10c63dd0(int A)
{
    if (Unknown08->Unknown20 && A > Unknown10)
        return A - Unknown10;
    return -1;
}
