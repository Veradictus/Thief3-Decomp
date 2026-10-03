// Game/Unsorted_109396A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10939730_Entry
{
    char Unknown00[8];
    Struct_10939730_Entry* Next;
};

struct Struct_10939730_Table
{
    char Unknown00[0xC];
    int Count;
    char Unknown10[4];
    Struct_10939730_Entry** Items;
};

class Class_10939730
{
public:
    void FUN_10939730();

    Struct_10939730_Entry* Current;
    Struct_10939730_Table* Container;
    int Index;
};

// FUNCTION: 0x10939730 ?FUN_10939730@Class_10939730@@QAEXXZ
void Class_10939730::FUN_10939730()
{
    if (Current)
    {
        Current = Current->Next;
        if (Current)
            return;
    }
    do {
        Index++;
        if (Index >= Container->Count) {
            Index = -1;
            return;
        }
        Current = Container->Items[Index];
    } while (Current == 0);
}
