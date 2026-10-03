// Game/Unsorted_10C24980.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BAEC80
{
public:
    void FUN_10c22ad0(const Class_10BAEC80& Other);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

struct Struct_10C24BC0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// An element of 0x24 bytes.
struct Item_10C24BC0
{
    int Unknown00;
    Struct_10C24BC0 Unknown04;
    int Unknown10;
    Class_10BAEC80 Unknown14;
    int Unknown20;
};

class Class_10C24940
{
public:
    int FUN_10c24bc0(const Item_10C24BC0& Item);
    void FUN_10c24260(int Count);

    int Unknown00;
    int Unknown04;
    Item_10C24BC0* Unknown08;
};

// FUNCTION: 0x10C24BC0 ?FUN_10c24bc0@Class_10C24940@@QAEHABUItem_10C24BC0@@@Z
int Class_10C24940::FUN_10c24bc0(const Item_10C24BC0& Item)
{
    int Index = Unknown00;
    FUN_10c24260(Index + 1);
    Item_10C24BC0* Dest = &Unknown08[Index];
    Dest->Unknown00 = Item.Unknown00;
    Dest->Unknown04 = Item.Unknown04;
    Dest->Unknown10 = Item.Unknown10;
    Dest->Unknown14.FUN_10c22ad0(Item.Unknown14);
    Dest->Unknown20 = Item.Unknown20;
    return Index;
}
