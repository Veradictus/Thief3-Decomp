// Game/Unsorted_10C064D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10C07300
{
public:
    void FUN_10c07300(int Item);

    char Unknown00[0x50];
    Class_10BFBD70 Unknown50;
};

// FUNCTION: 0x10C07300 ?FUN_10c07300@Class_10C07300@@QAEXH@Z
void Class_10C07300::FUN_10c07300(int Item)
{
    Unknown50.Append(Item);
}
