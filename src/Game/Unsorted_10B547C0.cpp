// Game/Unsorted_10B547C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B54920
{
public:
    void FUN_10b547c0(int A, int B);
    void FUN_10b54920(int A);

    int Unknown00;
    int Unknown04;
    char Unknown08[8];
    int* Unknown10;
    char Unknown14[4];
    int Unknown18;
};

// FUNCTION: 0x10B54920 ?FUN_10b54920@Class_10B54920@@QAEXH@Z
void Class_10B54920::FUN_10b54920(int A)
{
    if (Unknown00 < Unknown04)
        FUN_10b547c0(Unknown10[Unknown00], A);
    if (Unknown00 < Unknown04)
        FUN_10b547c0(Unknown18, A);
}
