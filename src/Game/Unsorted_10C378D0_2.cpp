// Game/Unsorted_10C378D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C37960
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void* Virtual5(int A, int B, int C, int D);
};

void FUN_10c378d0(Class_10C37960* Obj, void* Item, int Mode);

// FUNCTION: 0x10C37920 ?FUN_10c37920@@YA_NPAVClass_10C37960@@HHHHH@Z
bool FUN_10c37920(Class_10C37960* Obj, int A, int Mode, int B, int C, int D)
{
    void* Item = Obj->Virtual5(A, C, B, D);
    if (!Item)
        return false;
    FUN_10c378d0(Obj, Item, Mode);
    return true;
}
