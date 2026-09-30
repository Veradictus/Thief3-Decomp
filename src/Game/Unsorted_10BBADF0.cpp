// Game/Unsorted_10BBADF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

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

class Class_10BBB510
{
public:
    void FUN_10bbb510(int Item);

    char Unknown00[0x14];
    Class_10BFBD70 Unknown14;
};

struct Struct_10BA9EF0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BA9EF0
{
public:
    Struct_10BA9EF0 FUN_10ba9ef0();
};

class Class_10BBB8B0
{
public:
    void FUN_10bbb8b0();
    void FUN_10bbb580(const Struct_10BA9EF0& Position);

    char Unknown00[8];
    Class_10BA9EF0* Unknown08;
};

// FUNCTION: 0x10BBB510 ?FUN_10bbb510@Class_10BBB510@@QAEXH@Z
void Class_10BBB510::FUN_10bbb510(int Item)
{
    Unknown14.Append(Item);
}

// FUNCTION: 0x10BBB8B0 ?FUN_10bbb8b0@Class_10BBB8B0@@QAEXXZ
void Class_10BBB8B0::FUN_10bbb8b0()
{
    FUN_10bbb580(Unknown08->FUN_10ba9ef0());
}
