// Game/Unsorted_10A34780.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10EB7660
{
public:
    Class_10EB7660();

    virtual ~Class_10EB7660();

    char Unknown04[0x3C];
};

class Class_10E664A4 : public Class_10EB7660
{
public:
    Class_10E664A4();

    virtual ~Class_10E664A4();

    FArray Unknown40;
};

struct Entry_10A34D50
{
    char Unknown00[0x6C];
};

class Class_10A34D50
{
public:
    int FUN_10a34d50(const Entry_10A34D50& Item);
    void FUN_10a33fd0(int NewCount);

    int Unknown00;
    int Unknown04;
    Entry_10A34D50* Unknown08;
};

// FUNCTION: 0x10A34AC0 ??0Class_10E664A4@@QAE@XZ
Class_10E664A4::Class_10E664A4()
{
}

// FUNCTION: 0x10A34D50 ?FUN_10a34d50@Class_10A34D50@@QAEHABUEntry_10A34D50@@@Z
int Class_10A34D50::FUN_10a34d50(const Entry_10A34D50& Item)
{
    int Index = Unknown00;
    FUN_10a33fd0(Index + 1);
    Unknown08[Index] = Item;
    return Index;
}

// FUNCTION: 0x10A34D80 ??_GClass_10E664A4@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10A34AC0's definition in this unit.
