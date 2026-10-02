// Game/Unsorted_10C20DA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10C223A0
{
public:
    void FUN_10c20c70(int Count);
    void FUN_10c223a0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10C24940
{
public:
    void FUN_10c24260(int Count);
    void FUN_10c24940();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10C223A0 ?FUN_10c223a0@Class_10C223A0@@QAEXXZ
void Class_10C223A0::FUN_10c223a0()
{
    FUN_10c20c70(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10C24940 ?FUN_10c24940@Class_10C24940@@QAEXXZ
void Class_10C24940::FUN_10c24940()
{
    FUN_10c24260(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
