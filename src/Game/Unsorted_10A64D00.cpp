// Game/Unsorted_10A64D00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A64D50
{
public:
    void FUN_10a64d50();

    char Unknown00[0x8];
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    char Unknown14[0x4];
    int Unknown18;
    char Unknown1C[0x5];
    bool Unknown21;
    bool Unknown22;
};

class Class_10A64D00
{
public:
    void FUN_10a64d00(int A, int B, int C, int D, bool E, int F);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    bool Unknown20;
    bool Unknown21;
    bool Unknown22;
};

// FUNCTION: 0x10A64D00 ?FUN_10a64d00@Class_10A64D00@@QAEXHHHH_NH@Z
void Class_10A64D00::FUN_10a64d00(int A, int B, int C, int D, bool E, int F)
{
    Unknown10 = C;
    Unknown14 = D;
    Unknown00 = A;
    Unknown04 = B;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown1C = F;
    Unknown20 = E;
    Unknown18 = C;
    Unknown22 = false;
    Unknown21 = false;
}

// FUNCTION: 0x10A64D50 ?FUN_10a64d50@Class_10A64D50@@QAEXXZ
void Class_10A64D50::FUN_10a64d50()
{
    Unknown08 = 0;
    Unknown18 = Unknown10;
    Unknown0C = 0;
    Unknown21 = false;
    Unknown22 = false;
}
