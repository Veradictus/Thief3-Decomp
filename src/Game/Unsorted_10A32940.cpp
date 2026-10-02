// Game/Unsorted_10A32940.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10A32A70
{
public:
    void FUN_10a32940(int Count);
    void FUN_10a32a70();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10A32BF0
{
public:
    void FUN_10a32af0(int Count);
    void FUN_10a32bf0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10A32D60
{
public:
    void FUN_10a32c30(int Count);
    void FUN_10a32d60();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10A32A70 ?FUN_10a32a70@Class_10A32A70@@QAEXXZ
void Class_10A32A70::FUN_10a32a70()
{
    FUN_10a32940(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10A32BF0 ?FUN_10a32bf0@Class_10A32BF0@@QAEXXZ
void Class_10A32BF0::FUN_10a32bf0()
{
    FUN_10a32af0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10A32D60 ?FUN_10a32d60@Class_10A32D60@@QAEXXZ
void Class_10A32D60::FUN_10a32d60()
{
    FUN_10a32c30(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
