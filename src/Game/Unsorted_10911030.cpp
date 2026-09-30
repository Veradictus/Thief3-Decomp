// Game/Unsorted_10911030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10914D60
{
public:
    unsigned char FUN_10914d60();

    char Unknown00[0x8];
    unsigned char Field08;
};

class Class_10914D70
{
public:
    unsigned char FUN_10914d70();

    char Unknown00[0x9];
    unsigned char Field09;
};

extern float DAT_10f2c8dc;

extern float DAT_10f2c8e0;

class Class_10919b80
{
public:
    char Unknown00[0x28];
    int Field28;
    void FUN_10919b80(int p1);
};

class Class_10919ca0
{
public:
    char Unknown00[0x14];
    float Field14;
    float FUN_10919ca0(int p1);
};

class Class_1091CCF0
{
public:
    Class_1091CCF0();

    char Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

extern void* DAT_10e499f4[];

class Class_1091E340
{
public:
    void FUN_1091e340();

    void* VTable;
};

class Class_1091e360
{
public:
    char Unknown00[0x180];
    float Field180;
    float FUN_1091e360();
};

struct Class_1091E3E0 {
    char unknown_00[0x64];
    void* unknown_64;

    void* FUN_1091e3e0();
};

struct Class_1091E3F0 {
    char unknown_00[0xe4];
    void* unknown_e4;

    void* FUN_1091e3f0();
};

struct Class_1091E400 {
    char unknown_00[0x124];
    void* unknown_124;

    void* FUN_1091e400();
};

struct Class_1091E410 {
    char unknown_00[0x164];
    void* unknown_164;

    void* FUN_1091e410();
};

// FUNCTION: 0x10914D60 ?FUN_10914d60@Class_10914D60@@QAEEXZ
unsigned char Class_10914D60::FUN_10914d60()
{
    return Field08;
}

// FUNCTION: 0x10914D70 ?FUN_10914d70@Class_10914D70@@QAEEXZ
unsigned char Class_10914D70::FUN_10914d70()
{
    return Field09;
}

// FUNCTION: 0x10919120 ?FUN_10919120@@YAMXZ
float FUN_10919120()
{
    return DAT_10f2c8dc;
}

// FUNCTION: 0x10919180 ?FUN_10919180@@YAMXZ
float FUN_10919180()
{
    return DAT_10f2c8e0;
}

// FUNCTION: 0x10919B80 ?FUN_10919b80@Class_10919b80@@QAEXH@Z
void Class_10919b80::FUN_10919b80(int p1)
{
    Field28 = p1;
}

// FUNCTION: 0x10919CA0 ?FUN_10919ca0@Class_10919ca0@@QAEMH@Z
float Class_10919ca0::FUN_10919ca0(int p1)
{
    return Field14;
}

// FUNCTION: 0x1091CCF0 ??0Class_1091CCF0@@QAE@XZ
Class_1091CCF0::Class_1091CCF0()
{
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown18 = -1;
    Unknown14 = 0;
    Unknown1C = 0;
    Unknown00 = 0;
}

// FUNCTION: 0x1091E340 ?FUN_1091e340@Class_1091E340@@QAEXXZ
void Class_1091E340::FUN_1091e340()
{
    VTable = DAT_10e499f4;
}

// FUNCTION: 0x1091E360 ?FUN_1091e360@Class_1091e360@@QAEMXZ
float Class_1091e360::FUN_1091e360()
{
    return Field180;
}

// FUNCTION: 0x1091E3E0 ?FUN_1091e3e0@Class_1091E3E0@@QAEPAXXZ
void* Class_1091E3E0::FUN_1091e3e0() {
    return &unknown_64;
}

// FUNCTION: 0x1091E3F0 ?FUN_1091e3f0@Class_1091E3F0@@QAEPAXXZ
void* Class_1091E3F0::FUN_1091e3f0() {
    return &unknown_e4;
}

// FUNCTION: 0x1091E400 ?FUN_1091e400@Class_1091E400@@QAEPAXXZ
void* Class_1091E400::FUN_1091e400() {
    return &unknown_124;
}

// FUNCTION: 0x1091E410 ?FUN_1091e410@Class_1091E410@@QAEPAXXZ
void* Class_1091E410::FUN_1091e410() {
    return &unknown_164;
}
