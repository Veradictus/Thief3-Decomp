// Game/Unsorted_10B33E20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

struct Item_10B34130
{
    int Unknown00;
    Class_109081E0 Unknown04;
    Class_109081E0 Unknown08;
    int Unknown0C;
};

class Class_10B34130
{
public:
    int FUN_10b34130(const Item_10B34130* Item);
    void FUN_10b330d0(int NewCount);

    int Unknown00;
    int Unknown04;
    Item_10B34130* Unknown08;
};

// FUNCTION: 0x10B34130 ?FUN_10b34130@Class_10B34130@@QAEHPBUItem_10B34130@@@Z
int Class_10B34130::FUN_10b34130(const Item_10B34130* Item)
{
    int Index = Unknown00;
    FUN_10b330d0(Index + 1);
    Item_10B34130* Dest = &Unknown08[Index];
    Dest->Unknown00 = Item->Unknown00;
    Dest->Unknown04 = Item->Unknown04;
    Dest->Unknown08 = Item->Unknown08;
    Dest->Unknown0C = Item->Unknown0C;
    return Index;
}
