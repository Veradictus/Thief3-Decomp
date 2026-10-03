// Game/Unsorted_10A7DBB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E6BEA8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10a7dbb0(int Item);

    Class_10BFBD70 Unknown04;
    int Unknown10;
};

// FUNCTION: 0x10A7DBB0 ?FUN_10a7dbb0@Class_10E6BEA8@@UAEXH@Z
void Class_10E6BEA8::FUN_10a7dbb0(int Item)
{
    if (Item)
    {
        if (Unknown10 < Unknown04.Unknown00)
            Unknown04.Unknown08[Unknown10] = Item;
        else
            Unknown04.Append(Item);
        Unknown10++;
    }
}
