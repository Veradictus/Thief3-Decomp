// Game/Unsorted_10953EC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10953FA0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Item_10953AC0
{
    Struct_10953FA0 Unknown00;
    int Unknown0C;
};

class Class_10953AC0
{
public:
    void FUN_10953ac0(int A);

    int Unknown00;
    int Unknown04;
    Item_10953AC0* Unknown08;
};

class Class_10953FA0
{
public:
    void FUN_10953fa0(const Struct_10953FA0* A);

    char Unknown00[0x40];
    Class_10953AC0 Unknown40;
    char Unknown4C[8];
    int Unknown54;
};

class Class_10955AA0
{
public:
    void FUN_10955aa0(int Mode);

    char Unknown00[8];
    int Mode;
    char Unknown0C[4];
    int Unknown10;
    int Unknown14;
};

// FUNCTION: 0x10953FA0 ?FUN_10953fa0@Class_10953FA0@@QAEXPBUStruct_10953FA0@@@Z
void Class_10953FA0::FUN_10953fa0(const Struct_10953FA0* A)
{
    Item_10953AC0 Item;
    Item.Unknown00 = *A;
    Item.Unknown0C = Unknown54;
    Class_10953AC0* Array = &Unknown40;
    int Index = Array->Unknown00;
    Array->FUN_10953ac0(Index + 1);
    Array->Unknown08[Index] = Item;
}

// FUNCTION: 0x10955AA0 ?FUN_10955aa0@Class_10955AA0@@QAEXH@Z
void Class_10955AA0::FUN_10955aa0(int NewMode)
{
    Mode = NewMode;
    switch (NewMode)
    {
    case 2:
        Unknown14 = 1;
        Unknown10 = 0;
        break;
    case 6:
        Unknown14 = 1;
        Unknown10 = 2;
        break;
    case 4:
        Unknown14 = 0;
        Unknown10 = 0;
        break;
    case 0:
    case 8:
        Unknown14 = 0;
        Unknown10 = 2;
        break;
    default:
        Unknown14 = 0;
        Unknown10 = 2;
        break;
    }
}
