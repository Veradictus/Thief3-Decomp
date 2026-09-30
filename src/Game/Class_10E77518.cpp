// Game/Class_10E77518.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e77518[];

class Class_10E77518
{
public:
    Class_10E77518* FUN_10b0a9c0(int A, int B, int C, int D);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

// FUNCTION: 0x10B0A9C0 ?FUN_10b0a9c0@Class_10E77518@@QAEPAV1@HHHH@Z
Class_10E77518* Class_10E77518::FUN_10b0a9c0(int A, int B, int C, int D)
{
    Unknown04 = B;
    Unknown08 = C;
    Unknown00 = DAT_10e77518;
    Unknown0C = D;
    Unknown10 = A;
    return this;
}
