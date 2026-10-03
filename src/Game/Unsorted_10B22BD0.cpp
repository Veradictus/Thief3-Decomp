// Game/Unsorted_10B22BD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    virtual int Virtual8(int A);
};

class Class_10B22D60
{
public:
    void FUN_10b229c0(void** Slot, int Value);
    void FUN_10b22bd0(int A);

    char Unknown00[0x90];
    Class_10B22D60_Unknown90* Unknown90;
};

// FUNCTION: 0x10B22BD0 ?FUN_10b22bd0@Class_10B22D60@@QAEXH@Z
void Class_10B22D60::FUN_10b22bd0(int A)
{
    int Value = Unknown90->Virtual8(A);
    if (Value != Unknown90->Virtual4())
        FUN_10b229c0((void**)&Unknown90, Value);
}
