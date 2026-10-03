// Game/Unsorted_10A68150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10a58c70(const Class_10BFBD70& Other);
    void FUN_10bfbd70(int NewCount);
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

class Class_10A68150
{
public:
    void FUN_10a68150(int Item);

    char Unknown00[0x10];
    Class_10BFBD70 Unknown10;
};

// FUNCTION: 0x10A68150 ?FUN_10a68150@Class_10A68150@@QAEXH@Z
void Class_10A68150::FUN_10a68150(int Item)
{
    int Index = Unknown10.FindIndex(Item);
    if (Index != -1)
        Unknown10.FUN_109dff50(Index);
}
