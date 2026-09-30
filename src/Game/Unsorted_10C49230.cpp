// Game/Unsorted_10C49230.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10c4c2d0();

void FUN_10c51550();

void FUN_10c53200();

void FUN_10c562c0();

void FUN_10c57e70();

class Class_Field_10C58C80 {
public:
    void FUN_10c57e70();
};

class Class_10C58C80
{
public:
    Class_Field_10C58C80* Field00;
    void FUN_10c58c80();
};

class Class_10C49740
{
public:
    void FUN_10c49740(int* A, int B);
};

struct Info_10C58C90
{
    char Unknown00[0xDC];
    Class_10C49740 UnknownDC;
};

class Class_10C58C90
{
public:
    void FUN_10c58c90(int A, int B);

    Info_10C58C90* Unknown00;
};

// FUNCTION: 0x10C4CD50 ?FUN_10c4cd50@@YAXXZ
void FUN_10c4cd50()
{
    FUN_10c4c2d0();
}

// FUNCTION: 0x10C515F0 ?FUN_10c515f0@@YAXXZ
void FUN_10c515f0()
{
    FUN_10c51550();
}

// FUNCTION: 0x10C53230 ?FUN_10c53230@@YAXXZ
void FUN_10c53230()
{
    FUN_10c53200();
}

// FUNCTION: 0x10C56CF0 ?FUN_10c56cf0@@YAXXZ
void FUN_10c56cf0()
{
    FUN_10c562c0();
}

// FUNCTION: 0x10C58C80 ?FUN_10c58c80@Class_10C58C80@@QAEXXZ
void Class_10C58C80::FUN_10c58c80()
{
    Field00->FUN_10c57e70();
}

// FUNCTION: 0x10C58C90 ?FUN_10c58c90@Class_10C58C90@@QAEXHH@Z
void Class_10C58C90::FUN_10c58c90(int A, int B)
{
    int Value = A;
    Unknown00->UnknownDC.FUN_10c49740(&Value, B);
}
