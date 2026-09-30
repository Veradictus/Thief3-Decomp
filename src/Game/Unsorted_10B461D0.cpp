// Game/Unsorted_10B461D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AC92F0
{
public:
    void FUN_10ac92f0();
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x13C];
    Class_10AC92F0* Unknown13C;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10DD7640
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A);
};

Class_10DD7640* FUN_10dd7640();

// FUNCTION: 0x10B49170 ?FUN_10b49170@@YGXH@Z
void __stdcall FUN_10b49170(int Param)
{
    DAT_10f3a3d8->Unknown13C->FUN_10ac92f0();
    FUN_10dd7640()->Virtual2(0);
}
