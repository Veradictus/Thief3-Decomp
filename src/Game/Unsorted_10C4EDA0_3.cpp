// Game/Unsorted_10C4EDA0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10C4F970
{
public:
    void FUN_10c4f490(int Count);

    void Empty()
    {
        FUN_10c4f490(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10C4F9B0
{
public:
    void FUN_10c4f9b0();

    int Unknown00;
    Class_10C4F970 Unknown04;
};

// An array of 20-byte elements (count, capacity, data).
class Class_10C4E970
{
public:
    void FUN_10c4e910(const Class_10C4E970* Other);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

struct Item_10C50320
{
    Class_10C4E970 Unknown00;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

class Class_10C50320
{
public:
    int FUN_10c50320(const Item_10C50320* Item);
    void FUN_10c4f690(int NewCount);

    int Unknown00;
    int Unknown04;
    Item_10C50320* Unknown08;
};

// FUNCTION: 0x10C4F9B0 ?FUN_10c4f9b0@Class_10C4F9B0@@QAEXXZ
void Class_10C4F9B0::FUN_10c4f9b0()
{
    Unknown04.Empty();
}

// FUNCTION: 0x10C50320 ?FUN_10c50320@Class_10C50320@@QAEHPBUItem_10C50320@@@Z
int Class_10C50320::FUN_10c50320(const Item_10C50320* Item)
{
    int Index = Unknown00;
    FUN_10c4f690(Index + 1);
    Item_10C50320* Dest = &Unknown08[Index];
    Dest->Unknown0C = Item->Unknown0C;
    Dest->Unknown00.FUN_10c4e910(&Item->Unknown00);
    Dest->Unknown10 = Item->Unknown10;
    Dest->Unknown14 = Item->Unknown14;
    return Index;
}
