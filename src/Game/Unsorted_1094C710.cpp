// Game/Unsorted_1094C710.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1094D6E0
{
public:
    Class_1094D6E0* FUN_1094d6e0();

    char Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

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

class Class_1094CFD0
{
public:
    void FUN_1094cfd0(int Item);

    char Unknown00[0x12C];
    Class_10BFBD70 Unknown12C;
};

// FUNCTION: 0x1094CFD0 ?FUN_1094cfd0@Class_1094CFD0@@QAEXH@Z
void Class_1094CFD0::FUN_1094cfd0(int Item)
{
    Unknown12C.AddUnique(Item);
}

// FUNCTION: 0x1094D6E0 ?FUN_1094d6e0@Class_1094D6E0@@QAEPAV1@XZ
Class_1094D6E0* Class_1094D6E0::FUN_1094d6e0()
{
    Unknown04 = 0;
    Unknown00 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    return this;
}
