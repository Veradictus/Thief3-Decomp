// Game/Unsorted_10A16B60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A16B60
{
    short Unknown00;
    short Unknown02;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

class Class_10A163F0
{
public:
    int FUN_10a163f0(int* Key, Struct_10A16B60* Info);
};

class Class_10A16B60
{
public:
    int FUN_10a16b60(int Key, int B, int C, int D, int E, short F, short G);

    char Unknown00[4];
    Class_10A163F0 Unknown04;
};

// FUNCTION: 0x10A16B60 ?FUN_10a16b60@Class_10A16B60@@QAEHHHHHHFF@Z
int Class_10A16B60::FUN_10a16b60(int Key, int B, int C, int D, int E, short F, short G)
{
    if (Key == 0)
        return -1;
    Struct_10A16B60 Info;
    Info.Unknown04 = B;
    Info.Unknown08 = C;
    Info.Unknown0C = D;
    Info.Unknown10 = E;
    Info.Unknown00 = F;
    Info.Unknown02 = G;
    return Unknown04.FUN_10a163f0(&Key, &Info);
}
