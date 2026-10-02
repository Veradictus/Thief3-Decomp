// Game/Unsorted_10B90330.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B91800
{
public:
    Class_10B91800* FUN_10b91800(int A);
    void FUN_10b91320(int A);

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

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

class Class_10B912E0
{
public:
    void FUN_10b90980(int Count);
    void FUN_10b912e0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10B912E0 ?FUN_10b912e0@Class_10B912E0@@QAEXXZ
void Class_10B912E0::FUN_10b912e0()
{
    FUN_10b90980(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10B91800 ?FUN_10b91800@Class_10B91800@@QAEPAV1@H@Z
Class_10B91800* Class_10B91800::FUN_10b91800(int A)
{
    Unknown04 = 0;
    Unknown00 = 0;
    Unknown08 = 0;
    FUN_10b91320(A);
    return this;
}
