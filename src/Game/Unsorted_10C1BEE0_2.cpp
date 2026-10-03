// Game/Unsorted_10C1BEE0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e98fd8[];

class Class_10C1B840
{
public:
    Class_10C1B840(int A, int B, int C, int D, int E, float F);

    void** Unknown00;
    int Unknown04[17];
};

class Class_10E98FD8 : public Class_10C1B840
{
public:
    Class_10E98FD8* FUN_10c1bfb0(int A, int B, int C, int D, float E, float F, float G);

    int Unknown48;
    float Unknown4C;
};

// FUNCTION: 0x10C1BFB0 ?FUN_10c1bfb0@Class_10E98FD8@@QAEPAV1@HHHHMMM@Z
Class_10E98FD8* Class_10E98FD8::FUN_10c1bfb0(int A, int B, int C, int D, float E, float F, float G)
{
    this->Class_10C1B840::Class_10C1B840(C, A, B, (int)E, (int)F, 1.0f);
    Unknown48 = D;
    Unknown00 = DAT_10e98fd8;
    Unknown4C = G;
    return this;
}
