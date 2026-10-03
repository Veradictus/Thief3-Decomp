// Game/Unsorted_10B7ACC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7AD00
{
public:
    int FUN_10b7ad00(int Index);

    char Unknown00[0x28];
    int Unknown28;
    int Unknown2C;
    int* Unknown30;
};

class Class_109B5E00
{
public:
    void FUN_109b5e00(int A, int B, float C);
    void FUN_109b5f20(int A, int B, int C);
};

class Class_10B7ACC0
{
public:
    void FUN_10b7acc0(float Value, int Index);

    char Unknown00[4];
    Class_109B5E00* Unknown04;
    char Unknown08[0xC];
    int Unknown14;
    char Unknown18[0x1C];
    int Unknown34;
    char Unknown38[4];
    float* Unknown3C;
};

// FUNCTION: 0x10B7ACC0 ?FUN_10b7acc0@Class_10B7ACC0@@QAEXMH@Z
void Class_10B7ACC0::FUN_10b7acc0(float Value, int Index)
{
    if (Unknown34 > Index)
    {
        Unknown3C[Index] = Value;
        Unknown04->FUN_109b5e00(Unknown14, Index, Value);
        Unknown04->FUN_109b5f20(Unknown14, Index, 1);
    }
}

// FUNCTION: 0x10B7AD00 ?FUN_10b7ad00@Class_10B7AD00@@QAEHH@Z
int Class_10B7AD00::FUN_10b7ad00(int Index)
{
    if (Unknown28 > Index)
        return Unknown30[Index];
    return 0x101;
}
