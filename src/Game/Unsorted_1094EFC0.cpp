// Game/Unsorted_1094EFC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_1094F750
{
public:
    void FUN_1094f510(int A);
    void FUN_1094f750();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x1094F750 ?FUN_1094f750@Class_1094F750@@QAEXXZ
void Class_1094F750::FUN_1094f750()
{
    FUN_1094f510(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
