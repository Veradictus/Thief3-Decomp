// Game/Unsorted_10C62D70_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9CC20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int* FUN_10c62d70(int Index);

    char Unknown04[4];
    int Unknown08[6];
};

// FUNCTION: 0x10C62D70 ?FUN_10c62d70@Class_10E9CC20@@UAEPAHH@Z
int* Class_10E9CC20::FUN_10c62d70(int Index)
{
    if (Index < 0 || Index >= 6)
        Index = 0;
    return &Unknown08[Index];
}
