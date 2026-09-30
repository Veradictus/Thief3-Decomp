// Game/Unsorted_10B163C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B19540 {
public:
    char Unknown00[0x68];
    void* Field68;

    void* FUN_10b19540();
};

struct Struct_10B21250
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B21250
{
public:
    Struct_10B21250 FUN_10b21250();

    char Unknown00[0x400];
    Struct_10B21250 Unknown400;
};

class Class_10B212F0 {
public:
    char Unknown00[0x464];
    int Field464;
    void FUN_10b212f0();
};

class Class_10B21300 {
public:
    char Unknown00[0x464];
    int Field464;
    void FUN_10b21300();
};

class Class_10B21310 {
public:
    char Unknown00[0x464];
    int Field464;
    void FUN_10b21310();
};

class Class_10B21320 {
public:
    char Unknown00[0x464];
    int Field464;
    void FUN_10b21320();
};

class Class_10B21330 {
public:
    char Unknown00[0x464];
    int Field464;

    void FUN_10b21330();
};

class Class_10B21340 {
public:
    char Unknown00[0x464];
    int Field464;

    void FUN_10b21340();
};

class Class_10B21350 {
public:
    char Unknown00[0x464];
    int Field464;

    void FUN_10b21350();
};

class Class_10B21560
{
public:
    char Unknown00[0x490];
    int Field490;
    unsigned char FUN_10b21560();
};

class Class_10B21580 {
public:
    char Unknown00[0x32c];
    int Field32c;

    int FUN_10b21580();
};

class Class_10B21590
{
public:
    char Unknown00[0x32c];
    int Field32c;
    void FUN_10b21590(int param);
};

class Class_10B215A0 {
public:
    char Unknown00[0x32c];
    int Field32C;
    void FUN_10b215a0();
};

void FUN_10984d70();

class Class_10B24D60 {
public:
    char Unknown00[0x1c];
    unsigned char Field1C;
    unsigned char FUN_10b24d60();
};

// FUNCTION: 0x10B19540 ?FUN_10b19540@Class_10B19540@@QAEPAXXZ
void* Class_10B19540::FUN_10b19540()
{
    return &Field68;
}

// FUNCTION: 0x10B21250 ?FUN_10b21250@Class_10B21250@@QAE?AUStruct_10B21250@@XZ
Struct_10B21250 Class_10B21250::FUN_10b21250()
{
    return Unknown400;
}

// FUNCTION: 0x10B212F0 ?FUN_10b212f0@Class_10B212F0@@QAEXXZ
void Class_10B212F0::FUN_10b212f0()
{
    Field464 = 0x6;
}

// FUNCTION: 0x10B21300 ?FUN_10b21300@Class_10B21300@@QAEXXZ
void Class_10B21300::FUN_10b21300()
{
    Field464 = 0x2;
}

// FUNCTION: 0x10B21310 ?FUN_10b21310@Class_10B21310@@QAEXXZ
void Class_10B21310::FUN_10b21310()
{
    Field464 = 0x3;
}

// FUNCTION: 0x10B21320 ?FUN_10b21320@Class_10B21320@@QAEXXZ
void Class_10B21320::FUN_10b21320()
{
    Field464 = 0x4;
}

// FUNCTION: 0x10B21330 ?FUN_10b21330@Class_10B21330@@QAEXXZ
void Class_10B21330::FUN_10b21330()
{
    Field464 = 5;
}

// FUNCTION: 0x10B21340 ?FUN_10b21340@Class_10B21340@@QAEXXZ
void Class_10B21340::FUN_10b21340()
{
    Field464 = 1;
}

// FUNCTION: 0x10B21350 ?FUN_10b21350@Class_10B21350@@QAEXXZ
void Class_10B21350::FUN_10b21350()
{
    Field464 = 0;
}

// FUNCTION: 0x10B21560 ?FUN_10b21560@Class_10B21560@@QAEEXZ
unsigned char Class_10B21560::FUN_10b21560()
{
    return (Field490 & 1);
}

// FUNCTION: 0x10B21580 ?FUN_10b21580@Class_10B21580@@QAEHXZ
int Class_10B21580::FUN_10b21580()
{
    return Field32c;
}

// FUNCTION: 0x10B21590 ?FUN_10b21590@Class_10B21590@@QAEXH@Z
void Class_10B21590::FUN_10b21590(int param)
{
    Field32c = param;
}

// FUNCTION: 0x10B215A0 ?FUN_10b215a0@Class_10B215A0@@QAEXXZ
void Class_10B215A0::FUN_10b215a0()
{
    Field32C = 0x0;
}

// FUNCTION: 0x10B23B50 ?FUN_10b23b50@@YAXXZ
void FUN_10b23b50()
{
    FUN_10984d70();
}

// FUNCTION: 0x10B24D60 ?FUN_10b24d60@Class_10B24D60@@QAEEXZ
unsigned char Class_10B24D60::FUN_10b24d60()
{
    return Field1C;
}
