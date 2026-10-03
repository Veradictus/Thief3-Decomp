// Game/Unsorted_10A19020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_109dff50(int Index);

    int FindIndex(int Item)
    {
        for (int i = 0; i < Count; i++)
        {
            if (Data[i] == Item)
                return i;
        }
        return -1;
    }

    int Count;
    int Unknown04;
    int* Data;
};

class Class_10A19330
{
public:
    void FUN_10a19330(int Item, int Which);

    char Unknown00[8];
    Class_10BFBD70 Unknown08[1];
};

// FUNCTION: 0x10A19330 ?FUN_10a19330@Class_10A19330@@QAEXHH@Z
void Class_10A19330::FUN_10a19330(int Item, int Which)
{
    int Index = Unknown08[Which].FindIndex(Item);
    if (Index != -1)
        Unknown08[Which].FUN_109dff50(Index);
}
