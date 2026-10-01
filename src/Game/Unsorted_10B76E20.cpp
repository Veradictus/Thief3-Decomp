// Game/Unsorted_10B76E20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B78340
{
public:
    char Unknown00[0x188];
    void* Field188;

    void* FUN_10b78340();
};

extern void* DAT_10e888e4[];

extern void* DAT_10e68f94[];

class Class_10E888E4
{
public:
    Class_10E888E4* FUN_10b7a2f0();

    void** Unknown00;        // +0x00: DAT_10e888e4
    float Unknown04;
    int Unknown08;
    void** Unknown0C;        // +0x0c: DAT_10e68f94
    char Unknown10[0x3C];
    float Unknown4C;
};

class Class_10E822B0
{
public:
    Class_10E822B0();

    virtual ~Class_10E822B0();

    char Unknown04[0x150];
};

struct Base_10B7AA20
{
    int Unknown154;

    Base_10B7AA20()
    {
        Unknown154 = 0;
    }
};

struct Struct_10B7AA20
{
    int Unknown00;
    int Unknown04;

    Struct_10B7AA20()
    {
        Unknown00 = 0;
        Unknown04 = 0;
    }
};

class Class_10E88AF8 : public Class_10E822B0, public Base_10B7AA20
{
public:
    virtual ~Class_10E88AF8();
    Class_10E88AF8();

    Struct_10B7AA20 Unknown158;
};

class Class_10B7AC80 {
public:
    char Unknown00[0x40];
    unsigned char Field40;

    void FUN_10b7ac80(unsigned char param);
};

class Class_10B7B910 {
public:
    int Field00;

    Class_10B7B910* FUN_10b7b910();
};

void FUN_10da4310();

class Class_10B81A40
{
public:
    char Unknown00[0x70];
    float Field70;

    virtual float FUN_10b81a40();
};

class Class_10B81B10 {
public:
    char Unknown00[0x8c];
    int Field8c;
    int FUN_10b81b10();
};

void FUN_10b87e40();

void FUN_10b87e80();

void FUN_10b878f0();

extern void* DAT_10e89268[];

class Class_10B81D10 {
public:
    void* Field00;
    void FUN_10b81d10();
};

void FUN_10cad410();

// FUNCTION: 0x10B59E10 ??_GClass_10E88AF8@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B7AA20's definition in this unit.

// FUNCTION: 0x10B78340 ?FUN_10b78340@Class_10B78340@@QAEPAXXZ
void* Class_10B78340::FUN_10b78340()
{
    return Field188;
}

// FUNCTION: 0x10B7A2F0 ?FUN_10b7a2f0@Class_10E888E4@@QAEPAV1@XZ
Class_10E888E4* Class_10E888E4::FUN_10b7a2f0()
{
    Unknown04 = 1.0f;
    Unknown08 = 0;
    Unknown0C = DAT_10e68f94;
    Unknown4C = 32767.0f;
    Unknown00 = DAT_10e888e4;
    return this;
}

// FUNCTION: 0x10B7AA20 ??0Class_10E88AF8@@QAE@XZ
Class_10E88AF8::Class_10E88AF8()
{
}

// FUNCTION: 0x10B7AC80 ?FUN_10b7ac80@Class_10B7AC80@@QAEXE@Z
void Class_10B7AC80::FUN_10b7ac80(unsigned char param)
{
    Field40 = param;
}

// FUNCTION: 0x10B7B910 ?FUN_10b7b910@Class_10B7B910@@QAEPAV1@XZ
Class_10B7B910* Class_10B7B910::FUN_10b7b910()
{
    Field00 = -1;
    return this;
}

// FUNCTION: 0x10B7FB30 ?FUN_10b7fb30@@YAXXZ
void FUN_10b7fb30()
{
    FUN_10da4310();
}

// FUNCTION: 0x10B81A40 ?FUN_10b81a40@Class_10B81A40@@UAEMXZ
float Class_10B81A40::FUN_10b81a40()
{
    return Field70;
}

// FUNCTION: 0x10B81B10 ?FUN_10b81b10@Class_10B81B10@@QAEHXZ
int Class_10B81B10::FUN_10b81b10()
{
    return Field8c;
}

// FUNCTION: 0x10B81C20 ?FUN_10b81c20@@YAXXZ
void FUN_10b81c20()
{
    FUN_10b87e40();
}

// FUNCTION: 0x10B81C30 ?FUN_10b81c30@@YAXXZ
void FUN_10b81c30()
{
    FUN_10b87e80();
}

// FUNCTION: 0x10B81C40 ?FUN_10b81c40@@YAXXZ
void FUN_10b81c40()
{
    FUN_10b878f0();
}

// FUNCTION: 0x10B81D10 ?FUN_10b81d10@Class_10B81D10@@QAEXXZ
void Class_10B81D10::FUN_10b81d10()
{
    Field00 = DAT_10e89268;
}

// FUNCTION: 0x10B81D70 ?FUN_10b81d70@@YAXXZ
void FUN_10b81d70()
{
    FUN_10cad410();
}
