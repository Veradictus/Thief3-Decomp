// Game/Unsorted_10A68DB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A69130_Item
{
public:
    int Unknown00;
    int Unknown04;
    char Unknown08[0x20];
    int Unknown28;
};

class Class_10E6B5C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual Class_10A69130_Item* Virtual11(int A);
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void FUN_10a69130(int A, int** Out, int* Value);
};

// FUNCTION: 0x10A69130 ?FUN_10a69130@Class_10E6B5C0@@UAEXHPAPAHPAH@Z
void Class_10E6B5C0::FUN_10a69130(int A, int** Out, int* Value)
{
    Class_10A69130_Item* Item = Virtual11(A);
    if (!Item)
    {
        *Value = 0;
        *Out = 0;
        return;
    }
    *Out = &Item->Unknown04;
    *Value = Item->Unknown28;
}
