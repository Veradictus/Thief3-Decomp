// Game/Unsorted_10925D80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10925d80
{
public:
    void FUN_10925d80(int Item);

    char Unknown00[0x8C];
    Class_10BFBD70 Unknown8C;
};

class Class_10925db0
{
public:
    void FUN_10925db0(int Item);

    char Unknown00[0x98];
    Class_10BFBD70 Unknown98;
};

// FUNCTION: 0x10925D80 ?FUN_10925d80@Class_10925d80@@QAEXH@Z
void Class_10925d80::FUN_10925d80(int Item)
{
    Unknown8C.Append(Item);
}

// FUNCTION: 0x10925DB0 ?FUN_10925db0@Class_10925db0@@QAEXH@Z
void Class_10925db0::FUN_10925db0(int Item)
{
    Unknown98.Append(Item);
}
