// Game/Unsorted_10B22C40_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B22D60
{
public:
    void FUN_10b229c0(void** Slot, int Value);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[0x88];
};

class Class_10B22D20_Unknown90
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
    virtual void Virtual9();
    virtual void Virtual10();
    virtual int Virtual11(int A);
};

class Class_10B22D20 : public Class_10B22D60
{
public:
    void FUN_10b22d20();

    Class_10B22D20_Unknown90* Unknown90;
};

// FUNCTION: 0x10B22D20 ?FUN_10b22d20@Class_10B22D20@@QAEXXZ
void Class_10B22D20::FUN_10b22d20()
{
    int Value = Unknown90->Virtual11(Unknown04);
    if (Value != Unknown90->Virtual4())
        FUN_10b229c0((void**)&Unknown90, Value);
}
