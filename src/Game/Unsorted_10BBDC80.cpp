// Game/Unsorted_10BBDC80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10971570
{
public:
    void FUN_10971570(int A, bool* B);
};

class Class_10BBDC30
{
public:
    bool FUN_10bbd8b0(int A, bool* B);
    bool FUN_10bbdc30(int A);
    bool FUN_10bbdcc0(int A);

    char Unknown00[0xC];
    Class_10971570* Unknown0C;
    char Unknown10[4];
    Class_10971570* Unknown14;
};

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

// FUNCTION: 0x10BBDC80 ?FUN_10bbdc80@Class_10BBDB40@@QAEMH@Z
float Class_10BBDB40::FUN_10bbdc80(int A)
{
    float Result = 0.0f;
    if (FUN_10bbd870(A, &Result) != true)
        Unknown10->FUN_1098e330(A, (int*)&Result);
    return Result;
}

// FUNCTION: 0x10BBDCC0 ?FUN_10bbdcc0@Class_10BBDC30@@QAE_NH@Z
bool Class_10BBDC30::FUN_10bbdcc0(int A)
{
    bool Result = false;
    if (FUN_10bbd8b0(A, &Result) != true)
        Unknown14->FUN_10971570(A, &Result);
    return Result;
}
