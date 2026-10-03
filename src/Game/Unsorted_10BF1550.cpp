// Game/Unsorted_10BF1550.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BEFA30
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BEFA30
{
public:
    Class_10BEFA30& operator=(const Class_10BEFA30& A)
    {
        Unknown04 = A.Unknown04;
        Unknown10 = A.Unknown10;
        Unknown14 = A.Unknown14;
        Unknown18 = A.Unknown18;
        Unknown1C = A.Unknown1C;
        Unknown20 = A.Unknown20;
        return *this;
    }

    char Unknown00[4];
    Struct_10BEFA30 Unknown04;
    int Unknown10;
    int Unknown14;
    unsigned char Unknown18;
    int Unknown1C;
    int Unknown20;
};

class Class_10BF0A60
{
public:
    int FUN_10bf15d0(const Class_10BEFA30& Item);
    void FUN_10befb10(int Count);

    int Unknown00;
    int Unknown04;
    Class_10BEFA30* Unknown08;
};

// FUNCTION: 0x10BF15D0 ?FUN_10bf15d0@Class_10BF0A60@@QAEHABVClass_10BEFA30@@@Z
int Class_10BF0A60::FUN_10bf15d0(const Class_10BEFA30& Item)
{
    int Index = Unknown00;
    FUN_10befb10(Index + 1);
    Unknown08[Index] = Item;
    return Index;
}
