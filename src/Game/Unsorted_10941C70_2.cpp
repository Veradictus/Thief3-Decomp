// Game/Unsorted_10941C70_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109418E0
{
public:
    void FUN_109418e0(void* A, int B, int C);

    char Unknown00[6];
    char Unknown06;
    char Unknown07[0x31];
    int Unknown38;
};

class Class_10941C40
{
public:
    void FUN_10941b10(int A);
    void FUN_10941c70(void* A, int B, int C, int D);

    char Unknown00[0x10];
    int Unknown10;
    char Unknown14[8];
    Class_109418E0* Unknown1C;
};

// FUNCTION: 0x10941C70 ?FUN_10941c70@Class_10941C40@@QAEXPAXHHH@Z
void Class_10941C40::FUN_10941c70(void* A, int B, int C, int D)
{
    Unknown10 = B;
    if (Unknown1C == 0)
        FUN_10941b10(0);
    int Value = Unknown10;
    Class_109418E0* Item = Unknown1C;
    Item->Unknown06 = 0;
    Item->Unknown38 = Value;
    Item->FUN_109418e0(A, C, D);
}
