// Game/Unsorted_10BCBEC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    int FUN_1098e330(int Id, int* Out);
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10BCBEC0
{
    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

class Class_10E94578
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

    void FUN_10bc5b50();
};

class Class_10E92730 : public Class_10E94578
{
public:
    virtual void FUN_10bcbec0();

    Struct_10BCBEC0* Unknown04;
};

// FUNCTION: 0x10BCBEC0 ?FUN_10bcbec0@Class_10E92730@@UAEXXZ
void Class_10E92730::FUN_10bcbec0()
{
    int Value = 1;
    Class_10c7d570* Props = Unknown04->Unknown08;
    if (((Class_1098E330*)Props->FUN_10c7d570())->FUN_1098e330(0x80028b, &Value) && !Value)
        FUN_10bc5b50();
}
