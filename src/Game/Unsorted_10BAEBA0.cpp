// Game/Unsorted_10BAEBA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10BAEC00
{
public:
    void FUN_10bae100(int Count);
    void FUN_10baec00();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10BAEC40
{
public:
    void FUN_10bae1d0(int Count);
    void FUN_10baec40();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10BAEC80
{
public:
    void FUN_10a211e0(int Count);
    void FUN_10baec80();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10BAEC00 ?FUN_10baec00@Class_10BAEC00@@QAEXXZ
void Class_10BAEC00::FUN_10baec00()
{
    FUN_10bae100(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10BAEC40 ?FUN_10baec40@Class_10BAEC40@@QAEXXZ
void Class_10BAEC40::FUN_10baec40()
{
    FUN_10bae1d0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10BAEC80 ?FUN_10baec80@Class_10BAEC80@@QAEXXZ
void Class_10BAEC80::FUN_10baec80()
{
    FUN_10a211e0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
