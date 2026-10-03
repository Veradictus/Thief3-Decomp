// Game/Unsorted_10C084A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);
    void FUN_109dff50(int Index);
    void FUN_10c08510(int Item);
    void FUN_10c08550(int Item);

    int FindIndex(int Item)
    {
        for (int i = 0; i < Unknown00; i++)
        {
            if (Unknown08[i] == Item)
                return i;
        }
        return -1;
    }

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

// FUNCTION: 0x10C08510 ?FUN_10c08510@Class_10BFBD70@@QAEXH@Z
void Class_10BFBD70::FUN_10c08510(int Item)
{
    if (FindIndex(Item) == -1)
        Append(Item);
}

// FUNCTION: 0x10C08550 ?FUN_10c08550@Class_10BFBD70@@QAEXH@Z
void Class_10BFBD70::FUN_10c08550(int Item)
{
    int Index = FindIndex(Item);
    if (Index != -1)
        FUN_109dff50(Index);
}
