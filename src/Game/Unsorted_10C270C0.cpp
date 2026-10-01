// Game/Unsorted_10C270C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C270C0_Member
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
    virtual void F1B() = 0;
    virtual void F1C() = 0;
    virtual void F1D() = 0;
    virtual void F1E() = 0;
    virtual void F1F() = 0;
    virtual void F20() = 0;
    virtual void F21() = 0;
    virtual void F22() = 0;
};

class Class_10C270C0
{
public:
    char Unknown00[4];
    Class_10C270C0_Member* Unknown04;
    void FUN_10c270c0();
};

class Object_10C270D0
{
public:
    virtual ~Object_10C270D0();
};

class Class_10C270D0
{
public:
    void FUN_10c270d0();

    char Unknown00[0x44];
    bool Unknown44;
    bool Unknown45;
    char Unknown46[2];
    Object_10C270D0* Unknown48;
};

class Class_10C273E0
{
public:
    bool FUN_10c273e0(int Bit);

    int Unknown00;
    unsigned Unknown04;
};

// FUNCTION: 0x10C270C0 ?FUN_10c270c0@Class_10C270C0@@QAEXXZ
void Class_10C270C0::FUN_10c270c0()
{
    Unknown04->F22();
}

// FUNCTION: 0x10C270D0 ?FUN_10c270d0@Class_10C270D0@@QAEXXZ
void Class_10C270D0::FUN_10c270d0()
{
    if (Unknown48)
    {
        delete Unknown48;
        Unknown48 = 0;
    }
    Unknown44 = false;
    Unknown45 = true;
}

// FUNCTION: 0x10C273E0 ?FUN_10c273e0@Class_10C273E0@@QAE_NH@Z
bool Class_10C273E0::FUN_10c273e0(int Bit)
{
    if (Bit == 0)
        return Unknown04 == 0;
    return (Unknown04 & (1 << Bit)) != 0;
}
