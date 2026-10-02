// Game/Unsorted_10A67ED0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

struct Item_10943600
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10943600
{
public:
    void FUN_10da4f50(int NewCount);

    void Empty()
    {
        FUN_10da4f50(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    int Unknown00;
    int Unknown04;
    Item_10943600* Unknown08;
};

class Class_10A680C0
{
public:
    void FUN_10a680c0();

    int Unknown00;
    int Unknown04;
    Class_10943600 Unknown08;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int FindIndex(int Item)
    {
        for (int i = 0; i < Unknown00; i++)
        {
            if (Unknown08[i] == Item)
                return i;
        }
        return -1;
    }

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

class Class_10A68100
{
public:
    void FUN_10a68100(int Item);

    char Unknown00[0x10];
    Class_10BFBD70 Unknown10;
};

// FUNCTION: 0x10A680C0 ?FUN_10a680c0@Class_10A680C0@@QAEXXZ
void Class_10A680C0::FUN_10a680c0()
{
    Unknown08.Empty();
}

// FUNCTION: 0x10A68100 ?FUN_10a68100@Class_10A68100@@QAEXH@Z
void Class_10A68100::FUN_10a68100(int Item)
{
    if (Unknown10.FindIndex(Item) == -1)
        Unknown10.Append(Item);
}
