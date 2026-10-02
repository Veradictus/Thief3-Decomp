// Game/Unsorted_10BDF210.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BB85B0
{
public:
    void FUN_10bb85b0(unsigned char A);
};

class Class_109E3C90
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
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();

    void FUN_109e3c90(int A);
};

class Class_10D660B0 : public Class_109E3C90
{
public:
    void FUN_10d660b0();
};

class Class_10E95050 : public Class_10D660B0
{
public:
    virtual void FUN_10bdf2f0();

    Class_10BB85B0* Unknown04;
};

// FUNCTION: 0x10BDF2F0 ?FUN_10bdf2f0@Class_10E95050@@UAEXXZ
void Class_10E95050::FUN_10bdf2f0()
{
    Unknown04->FUN_10bb85b0(0);
    FUN_10d660b0();
    FUN_109e3c90(0);
}
