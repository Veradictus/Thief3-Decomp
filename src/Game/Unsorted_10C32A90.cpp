// Game/Unsorted_10C32A90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    void Append(int Item)
    {
        int Index = Unknown00;
        FUN_10bfbd70(Index + 1);
        Unknown08[Index] = Item;
    }

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E9AC80
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
    virtual void FUN_10c32af0(int Item);

    char Unknown04[0x134];
    Class_10BFBD70 Unknown138;
};

// FUNCTION: 0x10C32AF0 ?FUN_10c32af0@Class_10E9AC80@@UAEXH@Z
void Class_10E9AC80::FUN_10c32af0(int Item)
{
    for (int i = 0; i < Unknown138.Unknown00; i++)
    {
        if (Unknown138.Unknown08[i] == Item)
            return;
    }
    Unknown138.Append(Item);
}
