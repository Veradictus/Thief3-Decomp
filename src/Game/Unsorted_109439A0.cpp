// Game/Unsorted_109439A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10946B20
{
public:
    void FUN_10946b20();
    void FUN_109464c0(int a, int b);
};

struct Entry_10946110
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
};

class Class_10946110
{
public:
    int FUN_10946110(const Entry_10946110* Item);
    void FUN_10943350(int NewCount);

    int Unknown00;
    int Unknown04;
    Entry_10946110* Unknown08;
};

// FUNCTION: 0x10946110 ?FUN_10946110@Class_10946110@@QAEHPBUEntry_10946110@@@Z
int Class_10946110::FUN_10946110(const Entry_10946110* Item)
{
    int Index = Unknown00;
    FUN_10943350(Index + 1);
    Unknown08[Index] = *Item;
    return Index;
}

// FUNCTION: 0x10946B20 ?FUN_10946b20@Class_10946B20@@QAEXXZ
void Class_10946B20::FUN_10946b20()
{
    FUN_109464c0(0, 1);
}
