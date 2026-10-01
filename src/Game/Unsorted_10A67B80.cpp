// Game/Unsorted_10A67B80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10a68270(int A, int B, int C, int D, int E, int F);

class Class_10A68D20
{
public:
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

void FUN_10a67da0(int A, int B, int C, int D, int E, int F, int G);

// FUNCTION: 0x10A67EA0 ?FUN_10a67ea0@@YAXPAVClass_10A68D20@@HHHHH@Z
void FUN_10a67ea0(Class_10A68D20* Owner, int A, int B, int C, int D, int E)
{
    FUN_10a67da0(Owner->Unknown00, Owner->Unknown08, A, B, C, D, E);
}

// FUNCTION: 0x10A683D0 ?FUN_10a683d0@@YAXHHHHH@Z
void FUN_10a683d0(int A, int B, int C, int D, int E)
{
    FUN_10a68270(A, B, C, D, E, 0);
}
