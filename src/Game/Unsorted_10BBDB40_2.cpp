// Game/Unsorted_10BBDB40_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10971570
{
public:
    void FUN_10971570(int A, bool* B);
};

class Class_10BBDC30
{
public:
    bool FUN_10bbd8b0(int A, bool* B);

    char Unknown00[8];
};

class Class_10BBDB40 : public Class_10BBDC30
{
public:
    unsigned char FUN_10bbdb80(int A);

    Class_10971570* Unknown08;
};

// FUNCTION: 0x10BBDB80 ?FUN_10bbdb80@Class_10BBDB40@@QAEEH@Z
unsigned char Class_10BBDB40::FUN_10bbdb80(int A)
{
    bool Result = false;
    if (FUN_10bbd8b0(A, &Result) != 1)
        Unknown08->FUN_10971570(A, &Result);
    return Result;
}
