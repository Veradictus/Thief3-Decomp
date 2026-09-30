// Game/Unsorted_10C62D30_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10ff711c;

class Class_10E9CC20 {
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3(int p1) = 0;
    virtual void FUN_10c62d60();
};

class Class_10C639E0_Member
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
    virtual void F13(int p1) = 0;
};

class Class_10C639E0
{
public:
    char Unknown00[8];
    Class_10C639E0_Member* Unknown08;

    void FUN_10c639e0(int p1);
};

class Class_10C63A00_Member {
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
};

class Class_10C63A00 {
public:
    char Unknown00[8];
    Class_10C63A00_Member* Unknown08;
    void FUN_10c63a00();
};

class Class_10C63A30_Member {
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
};

class Class_10C63A30 {
public:
    char Unknown00[8];
    Class_10C63A30_Member* Unknown08;
    void FUN_10c63a30();
};

class Class_10E6AC98 {
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
    virtual void FUN_10c63a40(int p1);
    char Unknown04[0x18];
    int Unknown1c;
};

// FUNCTION: 0x10C62D60 ?FUN_10c62d60@Class_10E9CC20@@UAEXXZ
void Class_10E9CC20::FUN_10c62d60()
{
    Virtual3(DAT_10ff711c);
}

// FUNCTION: 0x10C639E0 ?FUN_10c639e0@Class_10C639E0@@QAEXH@Z
void Class_10C639E0::FUN_10c639e0(int p1)
{
    Unknown08->F13(p1);
}

// FUNCTION: 0x10C63A00 ?FUN_10c63a00@Class_10C63A00@@QAEXXZ
void Class_10C63A00::FUN_10c63a00()
{
    Unknown08->F15();
}

// FUNCTION: 0x10C63A30 ?FUN_10c63a30@Class_10C63A30@@QAEXXZ
void Class_10C63A30::FUN_10c63a30()
{
    Unknown08->F16();
}

// FUNCTION: 0x10C63A40 ?FUN_10c63a40@Class_10E6AC98@@UAEXH@Z
void Class_10E6AC98::FUN_10c63a40(int p1)
{
    Unknown1c = p1;
}
