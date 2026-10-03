// Game/Unsorted_10C4F490.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C4F870
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Item_10C4F870
{
    int Unknown00;
    Struct_10C4F870 Unknown04;
    float Unknown10;
};

class Class_10C4EDA0
{
public:
    void FUN_10a550b0(int Count);

    int Unknown00;
    int Unknown04;
    Item_10C4F870* Unknown08;
};

class Class_10C4F870
{
public:
    int FUN_10c4f870(const Struct_10C4F870& A, float B);

    char Unknown00[0x34];
    int Unknown34;
    Class_10C4EDA0 Unknown38;
};

// FUNCTION: 0x10C4F870 ?FUN_10c4f870@Class_10C4F870@@QAEHABUStruct_10C4F870@@M@Z
int Class_10C4F870::FUN_10c4f870(const Struct_10C4F870& A, float B)
{
    Item_10C4F870 Item;
    Item.Unknown00 = Unknown34++;
    Item.Unknown04 = A;
    Item.Unknown10 = B;
    Class_10C4EDA0* Array = &Unknown38;
    int Index = Array->Unknown00;
    Array->FUN_10a550b0(Index + 1);
    Array->Unknown08[Index] = Item;
    return Item.Unknown00;
}
