// Game/Unsorted_10C0C190.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Item_10C0C150
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C0C150
{
public:
    int FUN_10c0c150(const Item_10C0C150* Item);
    void FUN_10c0be50(int NewCount);
    void FUN_10c0c190(int Index);

    int Unknown00;
    int Unknown04;
    Item_10C0C150* Unknown08;
};

// FUNCTION: 0x10C0C190 ?FUN_10c0c190@Class_10C0C150@@QAEXH@Z
void Class_10C0C150::FUN_10c0c190(int Index)
{
    int Last = Unknown00 - 1;
    Item_10C0C150 Temp = Unknown08[Index];
    Unknown08[Index] = Unknown08[Last];
    Unknown08[Last] = Temp;
    FUN_10c0be50(Unknown00 - 1);
}
