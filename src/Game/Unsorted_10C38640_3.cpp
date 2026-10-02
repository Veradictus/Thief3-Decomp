// Game/Unsorted_10C38640_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9af80[];

double FUN_10c00480();

class Class_10E9AF80
{
public:
    Class_10E9AF80* FUN_10c3ceb0(int A, int B, int C);

    void** Unknown00;
    float Unknown04;
    float Unknown08;
    int Unknown0C;
    int Unknown10;
    float Unknown14;
    int Unknown18;
};

// FUNCTION: 0x10C3CEB0 ?FUN_10c3ceb0@Class_10E9AF80@@QAEPAV1@HHH@Z
Class_10E9AF80* Class_10E9AF80::FUN_10c3ceb0(int A, int B, int C)
{
    Unknown04 = 90.0f;
    Unknown08 = 90.0f;
    Unknown00 = DAT_10e9af80;
    Unknown0C = A;
    Unknown10 = B;
    Unknown14 = FUN_10c00480();
    Unknown18 = C;
    return this;
}
