// Game/Unsorted_10921150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10f3199c[];

void FUN_10926680();

extern void* DAT_10f31a7c[];

extern void* DAT_10f31ab0;

class Class_1092BA00
{
public:
    void FUN_1092ba00(int Param);
};

extern Class_1092BA00 DAT_10eff23c;

extern bool DAT_10f31aa4;

extern int DAT_10f31aa8;

extern int DAT_10f31b88;

class Class_1092D950 {
public:
    unsigned char FUN_1092d950();
    char Unknown00[0x7d];
    unsigned char Field7d;
};

extern int DAT_10f31a54;

// FUNCTION: 0x109249F0 ?FUN_109249f0@@YAXXZ
void FUN_109249f0()
{
    DAT_10f3199c[0] = 0;
}

// FUNCTION: 0x109275C0 ?FUN_109275c0@@YAXXZ
void FUN_109275c0()
{
    FUN_10926680();
}

// FUNCTION: 0x10928B20 ?FUN_10928b20@@YGXHHHHHHH@Z
void __stdcall FUN_10928b20(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
}

// FUNCTION: 0x10928BC0 ?FUN_10928bc0@@YAPAXXZ
void* FUN_10928bc0()
{
    return DAT_10f31a7c;
}

// FUNCTION: 0x109295B0 ?FUN_109295b0@@YAPAXXZ
void* FUN_109295b0()
{
    return *(void**)&DAT_10f31ab0;
}

// FUNCTION: 0x1092BB50 ?FUN_1092bb50@@YAXXZ
void FUN_1092bb50()
{
    if (!DAT_10f31aa4)
    {
        DAT_10eff23c.FUN_1092ba00(0x40);
        DAT_10f31aa4 = true;
        DAT_10f31aa8 = 0;
    }
}

// FUNCTION: 0x1092D410 ?FUN_1092d410@@YAXXZ
void FUN_1092d410()
{
    DAT_10f31b88 = 0;
}

// FUNCTION: 0x1092D950 ?FUN_1092d950@Class_1092D950@@QAEEXZ
unsigned char Class_1092D950::FUN_1092d950()
{
    return Field7d;
}

// FUNCTION: 0x1092FDD0 ?FUN_1092fdd0@@YAPAXXZ
void* FUN_1092fdd0()
{
    return (void*)DAT_10f31a54;
}
