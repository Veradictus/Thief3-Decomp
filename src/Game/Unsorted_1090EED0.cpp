// Game/Unsorted_1090EED0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090FF70
{
public:
    void FUN_1090fc80(int A);
    void FUN_1090ff70();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_1090FD40
{
public:
    int FUN_1090fd40(const Class_109081E0& Item);
    void FUN_1090f2c0(int Count);

    int Unknown00;
    int Unknown04;
    Class_109081E0* Unknown08;
};

// FUNCTION: 0x1090FD40 ?FUN_1090fd40@Class_1090FD40@@QAEHABVClass_109081E0@@@Z
int Class_1090FD40::FUN_1090fd40(const Class_109081E0& Item)
{
    int Index = Unknown00;
    FUN_1090f2c0(Index + 1);
    Unknown08[Index] = Item;
    return Index;
}

// FUNCTION: 0x1090FF70 ?FUN_1090ff70@Class_1090FF70@@QAEXXZ
void Class_1090FF70::FUN_1090ff70()
{
    FUN_1090fc80(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
