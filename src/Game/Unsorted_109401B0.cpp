// Game/Unsorted_109401B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10941980
{
    short Unknown00;
    short Unknown02;
    short Unknown04;
};

class Class_1091A4F0
{
public:
    void FUN_1091a4f0(int NewCount);

    int Unknown00;
    int Unknown04;
    Struct_10941980* Unknown08;
};

class Class_109418E0
{
public:
    char Unknown00[6];
    char Unknown06;
    char Unknown07[0x25];
    Class_1091A4F0 Unknown2C;
    int Unknown38;
};

class Class_10941C40
{
public:
    void FUN_10941980(short A, short B, short C);

    char Unknown00[0x10];
    int Unknown10;
    char Unknown14[8];
    Class_109418E0* Unknown1C;
};

// FUNCTION: 0x10941980 ?FUN_10941980@Class_10941C40@@QAEXFFF@Z
void Class_10941C40::FUN_10941980(short A, short B, short C)
{
    Class_109418E0* Item = Unknown1C;
    Struct_10941980 Value;
    Value.Unknown00 = A;
    Value.Unknown02 = B;
    Value.Unknown04 = C;
    Class_1091A4F0* Array = &Item->Unknown2C;
    Item->Unknown06 = 0;
    int Index = Array->Unknown00;
    Array->FUN_1091a4f0(Index + 1);
    Array->Unknown08[Index] = Value;
}
