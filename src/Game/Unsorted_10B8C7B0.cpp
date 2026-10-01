// Game/Unsorted_10B8C7B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10D9E5E0_Param;

class Class_10D9B090
{
public:
    void FUN_10d9e5e0(Struct_10D9E5E0_Param* A);
};

Class_10D9B090* FUN_10d9dcb0();

class Class_10B8C7B0
{
public:
    void FUN_10b8c7b0();
    void FUN_10b8cc60();

    char Unknown00[0x20];
    Struct_10D9E5E0_Param* Unknown20;
    bool Unknown24;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10B8DC70 : public Class_10BFBD70
{
public:
    void FUN_10b8dc70(int Item);
};

// FUNCTION: 0x10B8CC60 ?FUN_10b8cc60@Class_10B8C7B0@@QAEXXZ
void Class_10B8C7B0::FUN_10b8cc60()
{
    if (Unknown24)
    {
        FUN_10d9dcb0()->FUN_10d9e5e0(Unknown20);
        Unknown24 = false;
        FUN_10b8c7b0();
    }
}

// FUNCTION: 0x10B8DC70 ?FUN_10b8dc70@Class_10B8DC70@@QAEXH@Z
void Class_10B8DC70::FUN_10b8dc70(int Item)
{
    if (Item)
    {
        int Index = Unknown00;
        FUN_10bfbd70(Index + 1);
        Unknown08[Index] = Item;
    }
}
