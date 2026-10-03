// Game/Unsorted_10ABB6B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10ABB720
{
public:
    void FUN_10abb720(int Item);

    char Unknown00[0x10];
    Class_10BFBD70 Unknown10;
};

// FUNCTION: 0x10ABB720 ?FUN_10abb720@Class_10ABB720@@QAEXH@Z
void Class_10ABB720::FUN_10abb720(int Item)
{
    for (int i = 0; i < Unknown10.Unknown00; i++)
    {
        if (Item == Unknown10.Unknown08[i])
            return;
    }
    Unknown10.Append(Item);
}
