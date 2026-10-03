// Game/Unsorted_10929DC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);
    int FUN_1092a330(const int* Item);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

// FUNCTION: 0x1092A330 ?FUN_1092a330@Class_10BFBD70@@QAEHPBH@Z
int Class_10BFBD70::FUN_1092a330(const int* Item)
{
    int Count = Unknown00;
    for (int i = 0; i < Count; i++)
    {
        if (Unknown08[i] == *Item)
            return i;
    }
    FUN_10bfbd70(Count + 1);
    Unknown08[Count] = *Item;
    return Count;
}
