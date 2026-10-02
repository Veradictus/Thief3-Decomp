// Game/Unsorted_10A31620.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10A32270
{
public:
    void FUN_10a31f30(int Count);
    void FUN_10a32270();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10A32270 ?FUN_10a32270@Class_10A32270@@QAEXXZ
void Class_10A32270::FUN_10a32270()
{
    FUN_10a31f30(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
