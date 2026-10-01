// Game/Unsorted_10A16660.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A15B20
{
public:
    bool FUN_10a15b20(int* A);
};

class Class_10E5D688
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual bool FUN_10a166b0(int A);

    char Unknown04[4];
    Class_10A15B20 Unknown08;
};

// FUNCTION: 0x10A166B0 ?FUN_10a166b0@Class_10E5D688@@UAE_NH@Z
bool Class_10E5D688::FUN_10a166b0(int A)
{
    int Key = A;
    return Unknown08.FUN_10a15b20(&Key) == 1;
}
