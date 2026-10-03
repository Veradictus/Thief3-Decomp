// Game/Unsorted_10B22C40_5.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B22D60_Unknown90
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual int Virtual9(int A, int B);
};

class Class_10B22D60
{
public:
    void FUN_10b229c0(void** Slot, int Value);
    void FUN_10b22ce0(int A);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[0x88];
    Class_10B22D60_Unknown90* Unknown90;
};

// FUNCTION: 0x10B22CE0 ?FUN_10b22ce0@Class_10B22D60@@QAEXH@Z
void Class_10B22D60::FUN_10b22ce0(int A)
{
    int Value = Unknown90->Virtual9(Unknown04, A);
    if (Value != Unknown90->Virtual4())
        FUN_10b229c0((void**)&Unknown90, Value);
}
