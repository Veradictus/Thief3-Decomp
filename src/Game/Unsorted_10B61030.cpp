// Game/Unsorted_10B61030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A58B70
{
public:
    int FUN_10a58b70(int Index);
};

class Class_10B61080 : public Class_10A58B70
{
public:
    int FUN_10b61080(int Index);

    char Unknown00[0x1D4];
    int Unknown1D4;
    char Unknown1D8[0x24];
    int Unknown1FC;
};

class Class_10A51A40
{
public:
    void FUN_10a51a40(int A, int B);
};

class Class_10B61030
{
public:
    void FUN_10b61030(int A);

    char Unknown00[0x1DC];
    Class_10A51A40* Unknown1DC;
    char Unknown1E0[0x18];
    int Unknown1F8;
};

// FUNCTION: 0x10B61030 ?FUN_10b61030@Class_10B61030@@QAEXH@Z
void Class_10B61030::FUN_10b61030(int A)
{
    Unknown1F8 = A;
    if (Unknown1DC)
    {
        Unknown1DC->FUN_10a51a40(0, A);
        Unknown1DC->FUN_10a51a40(1, A);
        Unknown1DC->FUN_10a51a40(2, A);
    }
}

// FUNCTION: 0x10B61080 ?FUN_10b61080@Class_10B61080@@QAEHH@Z
int Class_10B61080::FUN_10b61080(int Index)
{
    int Result = FUN_10a58b70(Index);
    if (Unknown1D4 == 3)
        Result += Unknown1FC;
    return Result;
}
