// Game/Unsorted_1091CD10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1091E1F0
{
public:
    Class_1091E1F0* FUN_1091e1f0(int A, int B, int C, int D, int E, int F, int G, int H, int I);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

class Class_1091E2E0
{
public:
    void FUN_1091e2e0();

    int Unknown00;
    float Unknown04[4][4];
    int Unknown44;
    bool Unknown48;
    bool Unknown49;
    int Unknown4C;
    int Unknown50;
    int Unknown54;
    int Unknown58;
    int Unknown5C;
    int Unknown60;
};

// FUNCTION: 0x1091E1F0 ?FUN_1091e1f0@Class_1091E1F0@@QAEPAV1@HHHHHHHHH@Z
Class_1091E1F0* Class_1091E1F0::FUN_1091e1f0(int A, int B, int C, int D, int E, int F, int G, int H, int I)
{
    Unknown00 = A;
    Unknown04 = B;
    Unknown08 = C;
    Unknown0C = D;
    Unknown10 = E;
    Unknown14 = F;
    Unknown18 = G;
    Unknown1C = H;
    Unknown20 = I;
    return this;
}

// FUNCTION: 0x1091E2E0 ?FUN_1091e2e0@Class_1091E2E0@@QAEXXZ
void Class_1091E2E0::FUN_1091e2e0()
{
    Unknown04[0][0] = Unknown04[1][1] = Unknown04[2][2] = Unknown04[3][3] = 1.0f;
    Unknown04[0][3] = Unknown04[1][3] = Unknown04[2][3] = 0.0f;
    Unknown04[0][1] = Unknown04[0][2] = Unknown04[1][0] = 0.0f;
    Unknown04[3][0] = Unknown04[3][1] = Unknown04[3][2] = 0.0f;
    Unknown04[1][2] = Unknown04[2][0] = Unknown04[2][1] = 0.0f;
    Unknown44 = 0;
    Unknown48 = true;
    Unknown49 = false;
    Unknown4C = 0;
    Unknown50 = 0;
    Unknown54 = 0;
    Unknown5C = -1;
    Unknown60 = 0;
    Unknown58 = 0;
}
