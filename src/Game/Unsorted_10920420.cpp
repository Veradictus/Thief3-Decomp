// Game/Unsorted_10920420.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    void AddUnique(int Item)
    {
        int Count = Unknown00;
        for (int i = 0; i < Count; i++)
        {
            if (Unknown08[i] == Item)
                return;
        }
        FUN_10bfbd70(Count + 1);
        Unknown08[Count] = Item;
    }

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10920930
{
public:
    void FUN_10920930(int Item);

    char Unknown00[8];
    Class_10BFBD70 Unknown08;
};

// FUNCTION: 0x10920930 ?FUN_10920930@Class_10920930@@QAEXH@Z
void Class_10920930::FUN_10920930(int Item)
{
    Unknown08.AddUnique(Item);
}
