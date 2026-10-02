// Game/Unsorted_109E5770_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    int* Data;
};

class Class_10E5B2C0
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
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void FUN_109e60a0(int Index, const int* Item);

    char Unknown04[0xEC];
    Class_10BFBD70 Unknown0F0;
};

// FUNCTION: 0x109E60A0 ?FUN_109e60a0@Class_10E5B2C0@@UAEXHPBH@Z
void Class_10E5B2C0::FUN_109e60a0(int Index, const int* Item)
{
    if (Unknown0F0.Count < Index + 1)
        Unknown0F0.FUN_10bfbd70(Index + 1);
    Unknown0F0.Data[Index] = *Item;
}
