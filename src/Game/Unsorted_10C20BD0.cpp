// Game/Unsorted_10C20BD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C20D60
{
public:
    Class_10C20D60* FUN_10c20d60(int A, int B, char C);

    int Unknown00;
    int Unknown04;
    char Unknown08;
};

// FUNCTION: 0x10C20D60 ?FUN_10c20d60@Class_10C20D60@@QAEPAV1@HHD@Z
Class_10C20D60* Class_10C20D60::FUN_10c20d60(int A, int B, char C)
{
    Unknown00 = (A % 0xffff + 0xffff) % 0xffff;
    Unknown04 = (B % 0xffff + 0xffff) % 0xffff;
    Unknown08 = C;
    return this;
}
