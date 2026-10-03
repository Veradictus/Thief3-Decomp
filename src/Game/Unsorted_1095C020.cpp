// Game/Unsorted_1095C020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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

struct Struct_1095C2B0
{
    Struct_1095C2B0() : Unknown00(0x25), Unknown04(0) {}

    int Unknown00;
    int Unknown04;
};

class Class_1095C2B0
{
public:
    Class_1095C2B0* FUN_1095c2b0();

    Struct_1095C2B0 Unknown00;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

// FUNCTION: 0x1095C2B0 ?FUN_1095c2b0@Class_1095C2B0@@QAEPAV1@XZ
Class_1095C2B0* Class_1095C2B0::FUN_1095c2b0()
{
    Struct_1095C2B0 Temp;
    Unknown00 = Temp;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    return this;
}

// FUNCTION: 0x1095D720 ?FUN_1095d720@Class_1095D720@@QAEXHHH@Z
void Class_1095D720::FUN_1095d720(int A, int B, int C)
{
    Arg_10D52FA0 Flags;
    Flags.Unknown00 = 0;
    FUN_10d52fa0(A, B, C, this, Flags);
}
