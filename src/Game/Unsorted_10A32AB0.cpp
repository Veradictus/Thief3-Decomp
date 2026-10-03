// Game/Unsorted_10A32AB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A32AB0_Element
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

// A growable array: a count, the bytes allocated and the block.
class Class_10A32370
{
public:
    void FUN_10a32370(int NewCount);
    int FUN_10a32ab0(Class_10A32AB0_Element** A);

    int Unknown00;
    int Unknown04;
    Class_10A32AB0_Element** Unknown08;
};

// FUNCTION: 0x10A32AB0 ?FUN_10a32ab0@Class_10A32370@@QAEHPAPAVClass_10A32AB0_Element@@@Z
int Class_10A32370::FUN_10a32ab0(Class_10A32AB0_Element** A)
{
    int Index = Unknown00;
    FUN_10a32370(Index + 1);
    Class_10A32AB0_Element* Old = Unknown08[Index];
    Class_10A32AB0_Element* New = *A;
    Unknown08[Index] = New;
    if (New)
        New->Virtual1();
    if (Old)
        Old->Virtual2();
    return Index;
}
