// Game/Unsorted_10C2EEC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9AC80 {
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
    virtual bool FUN_10c2efc0();

    char Unknown04[0x9A];
    unsigned char Unknown9E;
};

class Class_10C2F090
{
public:
    char Unknown00[0x110];
    int Unknown110;
    void FUN_10c2f090(int p1);
};

class Class_10C2F330 {
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
    virtual void Virtual7() = 0;
    virtual void Virtual8() = 0;
    virtual void Virtual9() = 0;
    virtual void Virtual10() = 0;
    virtual void Virtual11() = 0;
    virtual void Virtual12() = 0;
    virtual void Virtual13() = 0;
    virtual void Virtual14() = 0;
    virtual void Virtual15() = 0;
    virtual void Virtual16() = 0;
    virtual void Virtual17() = 0;
    virtual void Virtual18() = 0;
    virtual void Virtual19() = 0;
    virtual void Virtual20() = 0;
    virtual void Virtual21() = 0;
    virtual void Virtual22() = 0;
    virtual void Virtual23() = 0;
    char Unknown04[0xd5];
    unsigned char Unknownd9;
    void FUN_10c2f330();
};

// FUNCTION: 0x10C2EFC0 ?FUN_10c2efc0@Class_10E9AC80@@UAE_NXZ
bool Class_10E9AC80::FUN_10c2efc0()
{
    return Unknown9E == 0;
}

// FUNCTION: 0x10C2F090 ?FUN_10c2f090@Class_10C2F090@@QAEXH@Z
void Class_10C2F090::FUN_10c2f090(int p1)
{
    Unknown110 = p1;
}

// FUNCTION: 0x10C2F330 ?FUN_10c2f330@Class_10C2F330@@QAEXXZ
void Class_10C2F330::FUN_10c2f330()
{
    Unknownd9 = 0;
    Virtual23();
}
