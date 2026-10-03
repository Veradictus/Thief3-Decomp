// Game/Unsorted_10BBDB40_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

class Class_10BBDC30
{
public:
    bool FUN_10bbd870(int A, float* B);
    float FUN_10bbdbc0(int A);

    char Unknown00[0xC];
    Class_1098E330* Unknown0C;
};

// FUNCTION: 0x10BBDBC0 ?FUN_10bbdbc0@Class_10BBDC30@@QAEMH@Z
float Class_10BBDC30::FUN_10bbdbc0(int A)
{
    float Result = 0.0f;
    if (FUN_10bbd870(A, &Result) != true)
        Unknown0C->FUN_1098e330(A, (int*)&Result);
    return Result;
}
