// Game/Unsorted_10C091A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_10913D70
{
public:
    Class_10913D70* FUN_10913d70(Class_10913D70* Other);

    int Unknown00;
    Class_109081E0 Unknown04;
};

struct Struct_10C091A0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// An element of 0x28 bytes.
struct Item_10C091A0
{
    int Unknown00;
    Class_10913D70 Unknown04;
    int Unknown0C;
    int Unknown10;
    Struct_10C091A0 Unknown14;
    int Unknown20;
    unsigned char Unknown24;
};

class Class_10C08E90
{
public:
    int FUN_10c091a0(Item_10C091A0* Item);
    void FUN_10c089b0(int Count);

    int Unknown00;
    int Unknown04;
    Item_10C091A0* Unknown08;
};

// FUNCTION: 0x10C091A0 ?FUN_10c091a0@Class_10C08E90@@QAEHPAUItem_10C091A0@@@Z
int Class_10C08E90::FUN_10c091a0(Item_10C091A0* Item)
{
    int Index = Unknown00;
    FUN_10c089b0(Index + 1);
    Item_10C091A0* Dest = &Unknown08[Index];
    Dest->Unknown04.FUN_10913d70(&Item->Unknown04);
    Dest->Unknown0C = Item->Unknown0C;
    Dest->Unknown10 = Item->Unknown10;
    Dest->Unknown14 = Item->Unknown14;
    Dest->Unknown20 = Item->Unknown20;
    Dest->Unknown24 = Item->Unknown24;
    return Index;
}
