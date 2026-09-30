// Game/Unsorted_10C00A50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C00A50 {
public:
    char Unknown00[8];
    int* Unknown08;
    int* FUN_10c00a50(int p1);
};

class Class_10c00c70
{
public:
    int Unknown00;
    bool FUN_10c00c70();
};

void FUN_10ad1dc0(void* Memory);

class Class_10C01F50
{
public:
    void FUN_10c01730(int A);
    void FUN_10c01f50();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10C01FC0
{
public:
    void FUN_10c016b0(int A);
    void FUN_10c01fc0();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

// FUNCTION: 0x10C00A50 ?FUN_10c00a50@Class_10C00A50@@QAEPAHH@Z
int* Class_10C00A50::FUN_10c00a50(int p1)
{
    return &Unknown08[p1];
}

// FUNCTION: 0x10C00C70 ?FUN_10c00c70@Class_10c00c70@@QAE_NXZ
bool Class_10c00c70::FUN_10c00c70()
{
    return Unknown00 > 0;
}

// FUNCTION: 0x10C01F50 ?FUN_10c01f50@Class_10C01F50@@QAEXXZ
void Class_10C01F50::FUN_10c01f50()
{
    FUN_10c01730(0x40);
    FUN_10ad1dc0(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

// FUNCTION: 0x10C01FC0 ?FUN_10c01fc0@Class_10C01FC0@@QAEXXZ
void Class_10C01FC0::FUN_10c01fc0()
{
    FUN_10c016b0(0x40);
    FUN_10ad1dc0(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
