// Game/Unsorted_10BDFAA0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10bf7f90
{
public:
    void FUN_10bf7f90(int A, int B);
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    int FUN_10bc4160();
};

class Class_10E95170 : public Class_10BC4160
{
public:
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
    virtual void FUN_10be02b0(int A);

    void FUN_10bdfef0();

    char Unknown04[0x3C];
    int Unknown40;
};

// FUNCTION: 0x10BE02B0 ?FUN_10be02b0@Class_10E95170@@UAEXH@Z
void Class_10E95170::FUN_10be02b0(int A)
{
    Class_10bf7f90* P = (Class_10bf7f90*)FUN_10bc4160();
    if (P)
    {
        P->FUN_10bf7f90(0, 1);
        Unknown40 = 0;
        FUN_10bdfef0();
    }
}
