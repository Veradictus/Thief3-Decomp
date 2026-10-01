// Game/Unsorted_109435D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109435D0
{
    char Unknown00[0x30];
};

class Class_109435D0
{
public:
    int FUN_109435d0(const Struct_109435D0& Item);
    void FUN_10942d20(int Count);

    int Unknown00;
    int Unknown04;
    Struct_109435D0* Unknown08;
};

struct Item_10943600
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10943600
{
public:
    int FUN_10943600(const Item_10943600* Item);
    void FUN_10da4f50(int NewCount);

    int Unknown00;
    int Unknown04;
    Item_10943600* Unknown08;
};

// FUNCTION: 0x109435D0 ?FUN_109435d0@Class_109435D0@@QAEHABUStruct_109435D0@@@Z
int Class_109435D0::FUN_109435d0(const Struct_109435D0& Item)
{
    int Index = Unknown00;
    FUN_10942d20(Index + 1);
    Unknown08[Index] = Item;
    return Index;
}

// FUNCTION: 0x10943600 ?FUN_10943600@Class_10943600@@QAEHPBUItem_10943600@@@Z
int Class_10943600::FUN_10943600(const Item_10943600* Item)
{
    int Index = Unknown00;
    FUN_10da4f50(Index + 1);
    Unknown08[Index] = *Item;
    return Index;
}
