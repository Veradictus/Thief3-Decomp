// Game/Unsorted_10BE2EE0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BB85E0
{
public:
    void FUN_10bb8ee0(int A);
};

class Class_10E94578
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
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void FUN_10bcac50(int A, int B, int C, int D, int E);

    void FUN_10bc5b50();
};

class Class_10E95D00 : public Class_10E94578
{
public:
    virtual void FUN_10be2ee0(int A, int B, int C, int D, int E);

    Class_10BB85E0* Unknown04;
};

// FUNCTION: 0x10BE2EE0 ?FUN_10be2ee0@Class_10E95D00@@UAEXHHHHH@Z
void Class_10E95D00::FUN_10be2ee0(int A, int B, int C, int D, int E)
{
    Class_10E94578::FUN_10bcac50(A, B, C, D, E);
    Unknown04->FUN_10bb8ee0(0);
    FUN_10bc5b50();
}
