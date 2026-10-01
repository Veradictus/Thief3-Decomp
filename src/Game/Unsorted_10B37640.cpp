// Game/Unsorted_10B37640.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B22D20
{
public:
    void FUN_10b22d20();
};

class Class_10AC92F0
{
public:
    void FUN_10ac92f0();
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x13C];
    Class_10AC92F0* Unknown13C;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

void FUN_10d660b0();

class Class_10B37FA0
{
public:
    void FUN_10b37640(int B, int C);
    void FUN_10b37fa0(int A, int B, int C);

    char Unknown00[8];
    Class_10B22D20* Unknown08;
};

class Class_10B48300
{
public:
    void FUN_10b48300(int A);
};

class Class_10E7C584
{
public:
    virtual void FUN_10b39500(int A);

    char Unknown04[0x08];
    Class_10B48300* Unknown0C[8];
};

class Class_10B47660
{
public:
    void FUN_10b47660(int A, int B);
};

class Class_10B3A460
{
public:
    Class_10B3A460* FUN_10b3a460(int A);

    char Unknown00[0x1C];
    int Unknown1C;
};

Class_10B3A460* FUN_10b3abf0();

class Class_10B39580
{
public:
    void FUN_10b39580(int A, int B);

    char Unknown00[0xC];
    Class_10B47660* Unknown0C[1];
};

// FUNCTION: 0x10B37FA0 ?FUN_10b37fa0@Class_10B37FA0@@QAEXHHH@Z
void Class_10B37FA0::FUN_10b37fa0(int A, int B, int C)
{
    Unknown08->FUN_10b22d20();
    FUN_10d660b0();
    DAT_10f3a3d8->Unknown13C->FUN_10ac92f0();
    FUN_10b37640(B, C);
}

// FUNCTION: 0x10B39500 ?FUN_10b39500@Class_10E7C584@@UAEXH@Z
void Class_10E7C584::FUN_10b39500(int A)
{
    for (int i = 0; i < 8; i++)
        Unknown0C[i]->FUN_10b48300(A);
}

// FUNCTION: 0x10B39580 ?FUN_10b39580@Class_10B39580@@QAEXHH@Z
void Class_10B39580::FUN_10b39580(int A, int B)
{
    int Index = FUN_10b3abf0()->FUN_10b3a460(A)->Unknown1C;
    Unknown0C[Index]->FUN_10b47660(A, B);
}
