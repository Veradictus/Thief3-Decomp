// Game/Unsorted_1095C020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10ad1dc0(void* Memory);

class Class_1095D6C0
{
public:
    void FUN_1095d6c0();

    char Unknown00[8];
    void* Unknown08;
    int Unknown0C;
    int Unknown10;
};

class Class_1095D720;

struct Arg_10D52FA0
{
    char Unknown00;
};

void FUN_10d52fa0(int A, int B, int C, Class_1095D720* Owner, Arg_10D52FA0 Flags);

class Class_1095D720
{
public:
    void FUN_1095d720(int A, int B, int C);
};

// FUNCTION: 0x1095D6C0 ?FUN_1095d6c0@Class_1095D6C0@@QAEXXZ
void Class_1095D6C0::FUN_1095d6c0()
{
    if (Unknown08)
        FUN_10ad1dc0(Unknown08);
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
}

// FUNCTION: 0x1095D720 ?FUN_1095d720@Class_1095D720@@QAEXHHH@Z
void Class_1095D720::FUN_1095d720(int A, int B, int C)
{
    Arg_10D52FA0 Flags;
    Flags.Unknown00 = 0;
    FUN_10d52fa0(A, B, C, this, Flags);
}
