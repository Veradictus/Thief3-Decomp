// Game/Unsorted_10C378D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C37960
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void* Virtual4(int A, int B, float C);
};

void FUN_10c378d0(Class_10C37960* Obj, void* Item, int Mode);

// FUNCTION: 0x10C37960 ?FUN_10c37960@@YA_NPAVClass_10C37960@@HHH@Z
bool FUN_10c37960(Class_10C37960* Obj, int A, int Mode, int B)
{
    void* Item = Obj->Virtual4(A, B, -1.0f);
    if (!Item)
        return false;
    FUN_10c378d0(Obj, Item, Mode);
    return true;
}
