// Game/Unsorted_10957D30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1095A7A0
{
public:
    Class_1095A7A0();

    char Unknown00[2];
    char Unknown02;
    char Unknown03;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

class Class_1095A1A0
{
public:
    void FUN_1095a1a0();

    char Unknown00[8];
    void* Unknown08;
};

class Class_1095A490
{
public:
    Class_1095A490* FUN_1095a490(float A, float B, float C, float D,
                                 float E, float F, float G, float H,
                                 float I, float J, float K, float L,
                                 float M, float N, float O, float P);

    float Unknown00[4][4];
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_1095A760
{
public:
    void FUN_1095a5a0(int A);
    void FUN_1095a760();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x1095A1A0 ?FUN_1095a1a0@Class_1095A1A0@@QAEXXZ
void Class_1095A1A0::FUN_1095a1a0()
{
    if (Unknown08)
        ::operator delete(Unknown08);
    Unknown08 = 0;
}

// FUNCTION: 0x1095A490 ?FUN_1095a490@Class_1095A490@@QAEPAV1@MMMMMMMMMMMMMMMM@Z
Class_1095A490* Class_1095A490::FUN_1095a490(float A, float B, float C, float D,
                                             float E, float F, float G, float H,
                                             float I, float J, float K, float L,
                                             float M, float N, float O, float P)
{
    Unknown00[0][0] = A;
    Unknown00[0][1] = B;
    Unknown00[0][2] = C;
    Unknown00[0][3] = D;
    Unknown00[1][0] = E;
    Unknown00[1][1] = F;
    Unknown00[1][2] = G;
    Unknown00[1][3] = H;
    Unknown00[2][0] = I;
    Unknown00[2][1] = J;
    Unknown00[2][2] = K;
    Unknown00[2][3] = L;
    Unknown00[3][0] = M;
    Unknown00[3][1] = N;
    Unknown00[3][2] = O;
    Unknown00[3][3] = P;
    return this;
}

// FUNCTION: 0x1095A760 ?FUN_1095a760@Class_1095A760@@QAEXXZ
void Class_1095A760::FUN_1095a760()
{
    FUN_1095a5a0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x1095A7A0 ??0Class_1095A7A0@@QAE@XZ
Class_1095A7A0::Class_1095A7A0()
{
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown02 = 0;
}
