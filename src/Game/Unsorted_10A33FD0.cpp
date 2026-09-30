// Game/Unsorted_10A33FD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10A34B90
{
public:
    void FUN_10a34b90(int A);
};

class Class_10A34CD0
{
public:
    void FUN_10a34cd0(int A);
};

class Class_10A35300
{
public:
    void FUN_10a35300(int A);

    char Unknown00[0x4];
    Class_10A34B90 Unknown04;
    char Unknown05[0x1B];
    Class_10A34CD0 Unknown20;
};

class Class_10A35630 {
    char Unknown00[0x74];
    void* Field74;
public:
    void FUN_10a35630(void* p1);
};

class Class_10A35680 {
    char Unknown00[0xc];
    unsigned char FieldC;
public:
    void FUN_10a35680(unsigned char p1);
};

class Class_10A357C0 {
    char Unknown00[0xa];
    unsigned char FieldA;
public:
    void FUN_10a357c0(unsigned char p1);
};

class Class_10A357D0 {
    char Unknown00[0x9];
    unsigned char Field9;
public:
    void FUN_10a357d0(unsigned char p1);
};

class Class_10A357E0 {
public:
    char Unknown00[0xb];
    unsigned char Field0b;
    void FUN_10a357e0(unsigned char param);
};

void FUN_10b10050();

void FUN_10b10110();

extern int DAT_10f39fe4;

extern int DAT_10f39fe8;

extern int DAT_10f39fec;

extern int DAT_10f39ff0;

extern FString DAT_10f39ff4;

extern FString DAT_10f3a000;

extern const char DAT_10e47660[];

extern void* DAT_10e666e0[];

class Class_10A39E70 {
    void* Field00;
public:
    void FUN_10a39e70();
};

extern void* DAT_10e66700[];

class Class_10A39EA0 {
    void* Field00;
public:
    void FUN_10a39ea0();
};

struct Class_10A3A020 {
    char unknown_00[0x144];
    void* Field_144;

    void* FUN_10a3a020(int p1);
};

struct Struct_10A3A1D0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A3A1D0
{
public:
    Struct_10A3A1D0 FUN_10a3a1d0();

    char Unknown00[0x114];
    Struct_10A3A1D0 Unknown114;
};

class Class_10A3A9C0 {
public:
    char Unknown00[0x12c];
    float Field12c;
    float FUN_10a3a9c0();
};

class Class_10A3D840_Target {
public:
    char Unknown00[0x218];
    int Field218;
};

class Class_10A3D840 {
public:
    char Unknown00[0x94];
    Class_10A3D840_Target* Field94;
    void FUN_10a3d840();
};

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

class Class_10A3D9E0
{
public:
    Class_10AF8250 FUN_10a3d9e0();

    char Unknown00[0x14];
    Class_10AF8250 Unknown14;
};

// FUNCTION: 0x10A35300 ?FUN_10a35300@Class_10A35300@@QAEXH@Z
void Class_10A35300::FUN_10a35300(int A)
{
    Unknown04.FUN_10a34b90(0x80);
    Unknown20.FUN_10a34cd0(0x80);
}

// FUNCTION: 0x10A35630 ?FUN_10a35630@Class_10A35630@@QAEXPAX@Z
void Class_10A35630::FUN_10a35630(void* p1)
{
    Field74 = p1;
}

// FUNCTION: 0x10A35680 ?FUN_10a35680@Class_10A35680@@QAEXE@Z
void Class_10A35680::FUN_10a35680(unsigned char p1)
{
    FieldC = p1;
}

// FUNCTION: 0x10A357C0 ?FUN_10a357c0@Class_10A357C0@@QAEXE@Z
void Class_10A357C0::FUN_10a357c0(unsigned char p1)
{
    FieldA = p1;
}

// FUNCTION: 0x10A357D0 ?FUN_10a357d0@Class_10A357D0@@QAEXE@Z
void Class_10A357D0::FUN_10a357d0(unsigned char p1)
{
    Field9 = p1;
}

// FUNCTION: 0x10A357E0 ?FUN_10a357e0@Class_10A357E0@@QAEXE@Z
void Class_10A357E0::FUN_10a357e0(unsigned char param)
{
    Field0b = param;
}

// FUNCTION: 0x10A36350 ?FUN_10a36350@@YAXXZ
void FUN_10a36350()
{
    FUN_10b10050();
}

// FUNCTION: 0x10A363E0 ?FUN_10a363e0@@YAXXZ
void FUN_10a363e0()
{
    FUN_10b10110();
}

// FUNCTION: 0x10A36BD0 ?FUN_10a36bd0@@YAHXZ
int FUN_10a36bd0()
{
    return DAT_10f39fe4;
}

// FUNCTION: 0x10A36C20 ?FUN_10a36c20@@YAHXZ
int FUN_10a36c20()
{
    return DAT_10f39fe8;
}

// FUNCTION: 0x10A36C30 ?FUN_10a36c30@@YAHXZ
int FUN_10a36c30()
{
    return DAT_10f39fec;
}

// FUNCTION: 0x10A36C60 ?FUN_10a36c60@@YAHXZ
int FUN_10a36c60()
{
    return DAT_10f39ff0;
}

// FUNCTION: 0x10A36C70 ?FUN_10a36c70@@YAXXZ
void FUN_10a36c70()
{
    DAT_10f39fe4 = 0;
    DAT_10f39ff4 = DAT_10e47660;
    DAT_10f3a000 = DAT_10e47660;
    DAT_10f39fe8 = 0;
}

// FUNCTION: 0x10A39E70 ?FUN_10a39e70@Class_10A39E70@@QAEXXZ
void Class_10A39E70::FUN_10a39e70()
{
    Field00 = (void*)DAT_10e666e0;
}

// FUNCTION: 0x10A39EA0 ?FUN_10a39ea0@Class_10A39EA0@@QAEXXZ
void Class_10A39EA0::FUN_10a39ea0()
{
    Field00 = (void*)DAT_10e66700;
}

// FUNCTION: 0x10A3A020 ?FUN_10a3a020@Class_10A3A020@@QAEPAXH@Z
void* Class_10A3A020::FUN_10a3a020(int p1)
{
    return &Field_144;
}

// FUNCTION: 0x10A3A1D0 ?FUN_10a3a1d0@Class_10A3A1D0@@QAE?AUStruct_10A3A1D0@@XZ
Struct_10A3A1D0 Class_10A3A1D0::FUN_10a3a1d0()
{
    return Unknown114;
}

// FUNCTION: 0x10A3A9C0 ?FUN_10a3a9c0@Class_10A3A9C0@@QAEMXZ
float Class_10A3A9C0::FUN_10a3a9c0()
{
    return Field12c;
}

