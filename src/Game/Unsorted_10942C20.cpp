// Game/Unsorted_10942C20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_109435A0
{
public:
    void FUN_10942c60(int A);
    void FUN_10943160();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

struct Struct_109434F0
{
    char Unknown00[0x20];
};

class Class_109434F0
{
public:
    int FUN_109434f0(const Struct_109434F0& Item);
    void FUN_10dcd540(int Count);

    int Unknown00;
    int Unknown04;
    Struct_109434F0* Unknown08;
};

class Class_10943520
{
public:
    void FUN_10943240(int A);
    void FUN_10943520();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

struct Entry_10946110;

class Class_10946110
{
public:
    void FUN_10943350(int NewCount);
    void FUN_10943560();

    int Unknown00;
    int Unknown04;
    Entry_10946110* Unknown08;
};

// FUNCTION: 0x10943160 ?FUN_10943160@Class_109435A0@@QAEXXZ
void Class_109435A0::FUN_10943160()
{
    FUN_10942c60(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x109434F0 ?FUN_109434f0@Class_109434F0@@QAEHABUStruct_109434F0@@@Z
int Class_109434F0::FUN_109434f0(const Struct_109434F0& Item)
{
    int Index = Unknown00;
    FUN_10dcd540(Index + 1);
    Unknown08[Index] = Item;
    return Index;
}

// FUNCTION: 0x10943520 ?FUN_10943520@Class_10943520@@QAEXXZ
void Class_10943520::FUN_10943520()
{
    FUN_10943240(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10943560 ?FUN_10943560@Class_10946110@@QAEXXZ
void Class_10946110::FUN_10943560()
{
    FUN_10943350(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
