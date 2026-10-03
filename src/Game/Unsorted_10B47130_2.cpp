// Game/Unsorted_10B47130_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7B460
{
public:
    void FUN_10b7b460(int A, int B, int C, int D);
};

class Class_Field0c_D
{
public:
    int FUN_10b47020(int A);

    char Unknown00[8];
    Class_10B7B460* Unknown08[2];
};

class Class_10B47130 : public Class_Field0c_D
{
public:
    void FUN_10b47130(int A, int B, int C, int D, int E);

    char Unknown10[4];
    int Unknown14;
    char Unknown18[0x20];
    int Unknown38;
    int Unknown3C;
};

// FUNCTION: 0x10B47130 ?FUN_10b47130@Class_10B47130@@QAEXHHHHH@Z
void Class_10B47130::FUN_10b47130(int A, int B, int C, int D, int E)
{
    int Index = FUN_10b47020(A);
    if (Index >= 0)
        Unknown08[Index]->FUN_10b7b460(B, C, D, E);
    else if (A == Unknown14)
    {
        Unknown38 = B;
        Unknown3C = C;
    }
}
