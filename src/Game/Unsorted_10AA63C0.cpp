// Game/Unsorted_10AA63C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C1F0
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
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual int FUN_10aa63c0(int index);

    char Unknown04[8];
    int* Unknown0C;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E6D8CC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10aa67a0(int Value);

    Class_10BFBD70 Unknown04;
};

// FUNCTION: 0x10AA63C0 ?FUN_10aa63c0@Class_10E6C1F0@@UAEHH@Z
int Class_10E6C1F0::FUN_10aa63c0(int index)
{
    return Unknown0C[index];
}

// FUNCTION: 0x10AA67A0 ?FUN_10aa67a0@Class_10E6D8CC@@UAEXH@Z
void Class_10E6D8CC::FUN_10aa67a0(int Value)
{
    Class_10BFBD70* Array = &Unknown04;
    int Index = Array->Unknown00;
    Array->FUN_10bfbd70(Index + 1);
    Array->Unknown08[Index] = Value;
}
