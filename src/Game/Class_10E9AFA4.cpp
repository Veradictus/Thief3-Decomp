// Game/Class_10E9AFA4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9afa4[];

class Class_10E9AFA4
{
public:
    Class_10E9AFA4* FUN_10c3cf70(int A, int B, int C);

    void* Unknown00;
    float Unknown04;
    float Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

// FUNCTION: 0x10C3CF70 ?FUN_10c3cf70@Class_10E9AFA4@@QAEPAV1@HHH@Z
Class_10E9AFA4* Class_10E9AFA4::FUN_10c3cf70(int A, int B, int C)
{
    Unknown04 = 90.0f;
    Unknown08 = 90.0f;
    Unknown0C = A;
    Unknown00 = DAT_10e9afa4;
    Unknown10 = B;
    Unknown14 = C;
    return this;
}
