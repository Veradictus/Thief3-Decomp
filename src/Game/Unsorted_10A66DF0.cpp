// Game/Unsorted_10A66DF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A66DF0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();

    bool FUN_10a66df0(int A);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10A66DF0 ?FUN_10a66df0@Class_10A66DF0@@QAE_NH@Z
bool Class_10A66DF0::FUN_10a66df0(int A)
{
    bool Result = false;
    if (Unknown08 && A)
    {
        Virtual3();
        Virtual4();
        Unknown08 = 0;
        Result = true;
    }
    return Result;
}
