// Game/Unsorted_10BBDB40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    int FUN_1098e330(int A, int* B);
};

class Class_10BBDB40
{
public:
    bool FUN_10bbd870(int A, float* B);
    float FUN_10bbdb40(int A);
    float FUN_10bbdc80(int A);

    char Unknown00[8];
    Class_1098E330* Unknown08;
    char Unknown0C[4];
    Class_1098E330* Unknown10;
};

// FUNCTION: 0x10BBDB40 ?FUN_10bbdb40@Class_10BBDB40@@QAEMH@Z
float Class_10BBDB40::FUN_10bbdb40(int A)
{
    float Result = 0.0f;
    if (FUN_10bbd870(A, &Result) != true)
        Unknown08->FUN_1098e330(A, (int*)&Result);
    return Result;
}
