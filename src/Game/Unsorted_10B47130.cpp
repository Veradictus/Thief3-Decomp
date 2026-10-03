// Game/Unsorted_10B47130.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7ACC0
{
public:
    void FUN_10b7acc0(int A, int B);
};

class Class_Field0c_D
{
public:
    int FUN_10b47020(int A);

    char Unknown00[8];
    Class_10B7ACC0* Unknown08[2];
};

class Class_10B47180 : public Class_Field0c_D
{
public:
    void FUN_10b47180(int A, int B, int C, int D);

    char Unknown10[4];
    int Unknown14;
    char Unknown18[0x24];
    int Unknown3C;
};

// FUNCTION: 0x10B47180 ?FUN_10b47180@Class_10B47180@@QAEXHHHH@Z
void Class_10B47180::FUN_10b47180(int A, int B, int C, int D)
{
    int Index = FUN_10b47020(A);
    if (Index >= 0)
        Unknown08[Index]->FUN_10b7acc0(C, D);
    else if (A == Unknown14)
        Unknown3C = C;
}
