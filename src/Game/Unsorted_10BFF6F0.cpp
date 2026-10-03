// Game/Unsorted_10BFF6F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10bbefa0
{
public:
    void* FUN_10bbefa0();
};

class Class_10bbefb0
{
public:
    void* FUN_10bbefb0();
};

class Class_10BFF600
{
public:
    int FUN_10bff600(int A, const float* B);
    void* FUN_10bff6f0(int A, const float* B, char C);
};

// FUNCTION: 0x10BFF6F0 ?FUN_10bff6f0@Class_10BFF600@@QAEPAXHPBMD@Z
void* Class_10BFF600::FUN_10bff6f0(int A, const float* B, char C)
{
    int Result = FUN_10bff600(A, B);
    if (!Result)
        return 0;
    if (C == 1)
        return ((Class_10bbefa0*)Result)->FUN_10bbefa0();
    return ((Class_10bbefb0*)Result)->FUN_10bbefb0();
}
