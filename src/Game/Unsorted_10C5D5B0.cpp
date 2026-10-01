// Game/Unsorted_10C5D5B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10c5d4f0
{
public:
    void FUN_10c5d400(int p1, int p2);
};

extern Class_10c5d4f0* DAT_10ff7108;

class Class_10C5DAD0;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10C5DAD0* p1);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10C5DAD0
{
public:
    void FUN_10c5dad0();
};

// FUNCTION: 0x10C5D5B0 ?FUN_10c5d5b0@@YA_NHH@Z
bool FUN_10c5d5b0(int p1, int p2)
{
    DAT_10ff7108->FUN_10c5d400(p2, p1);
    return true;
}

// FUNCTION: 0x10C5DAD0 ?FUN_10c5dad0@Class_10C5DAD0@@QAEXXZ
void Class_10C5DAD0::FUN_10c5dad0()
{
    if (DAT_10f46da0)
        DAT_10f46da0->Virtual2(this);
}
