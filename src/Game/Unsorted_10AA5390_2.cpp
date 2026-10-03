// Game/Unsorted_10AA5390_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Entry_10AA5390
{
    char Unknown00[0x1C];
};

class Class_10E6D600
{
public:
    virtual void Virtual0();
    virtual void FUN_10aa5390(const Entry_10AA5390& Item);
    virtual void Virtual2(int A);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Entry_10AA5390* Unknown10;
};

// FUNCTION: 0x10AA5390 ?FUN_10aa5390@Class_10E6D600@@UAEXABUEntry_10AA5390@@@Z
void Class_10E6D600::FUN_10aa5390(const Entry_10AA5390& Item)
{
    if (Unknown0C == Unknown08)
        Virtual2(1);
    Unknown10[(Unknown04 + Unknown0C) % Unknown08] = Item;
    Unknown0C++;
}
