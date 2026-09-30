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

// FUNCTION: 0x10B61080 ?FUN_10b61080@Class_10B61080@@QAEHH@Z
int Class_10B61080::FUN_10b61080(int Index)
{
    int Result = FUN_10a58b70(Index);
    if (Unknown1D4 == 3)
        Result += Unknown1FC;
    return Result;
}
