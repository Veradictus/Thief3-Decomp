// Game/Unsorted_10B364D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7c428[];

class Class_10B364D0 {
public:
    Class_10B364D0* FUN_10b364d0();
};

void FUN_10b476d0();

class Class_Field04
{
public:
    void FUN_10b476d0();
};

class Class_10B396A0
{
public:
    void FUN_10b396a0();

    char Unknown00[0xc];
    Class_Field04* Field0c;
};

class Class_10B3A470
{
public:
    Class_10B3A470* FUN_10b3a470();

    char Unknown00;
    char Unknown01;
    float Unknown04;
    float Unknown08;
    char Unknown0C[0xC];
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
};

class Class_10B3AC50 {
public:
    void FUN_10b3ac50(void* p1);
};

struct Static_10B3AC60
{
    int Unknown00;
    Static_10B3AC60() : Unknown00(0) {}
};

// Return float constant from data

extern float DAT_10e7e4b4;

// Return float constant from data

extern float DAT_10e7e4b8;

// OR field of parameter with immediate value

class Object_10B3ADC0 {
public:
    char Unknown00[0x450];
    int Field450;
};

class Class_10B3ADC0 {
public:
    void FUN_10b3adc0(Object_10B3ADC0* param);
};

struct Info_10B3E210
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

void FUN_10a58e50();

void FUN_10a51620();

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0x114];
};

class Class_10E7FED0 : public Class_10E67FD0
{
public:
    virtual ~Class_10E7FED0();
    Class_10E7FED0();

    FArray Unknown118;
};

void FUN_10b2bd00();

extern void* DAT_10e7fb00[];

struct Class_10E7FB00
{
    void* Unknown00;
    Class_10E7FB00() { Unknown00 = DAT_10e7fb00; }
};

void FUN_10b40820();

class Class_10B42340
{
public:
    Class_10B42340* FUN_10b42340(int A, int B);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    float Unknown14;
};

class Class_10B42640
{
public:
    char Unknown00[0x1c];
    int Field1C;

    void FUN_10b42640();
};

// Parameter setter at field offset 0x120

class Class_10B429A0 {
public:
    char Unknown00[0x120];
    int Field120;
    void FUN_10b429a0(int param);
};

class Class_10B43D40 {
public:
    char Unknown00[0x150];
    void* Field150;
    void FUN_10b43d40(void* p1);
};

extern const char DAT_10e80e74[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10B43D50
{
public:
    Class_109081E0 FUN_10b43d50();
};

class Class_10E81300 : public Class_10E67FD0
{
public:
    Class_10E81300();

    virtual ~Class_10E81300();

    char Unknown118[0x08];
    int Unknown120;
    int Unknown124;
    int Unknown128;
};

void FUN_10a53400();

// FUNCTION: 0x10B364D0 ?FUN_10b364d0@Class_10B364D0@@QAEPAV1@XZ
Class_10B364D0* Class_10B364D0::FUN_10b364d0()
{
    *(void**)this = DAT_10e7c428;
    return this;
}

// FUNCTION: 0x10B396A0 ?FUN_10b396a0@Class_10B396A0@@QAEXXZ
void Class_10B396A0::FUN_10b396a0()
{
    Field0c->FUN_10b476d0();
}

// FUNCTION: 0x10B3A470 ?FUN_10b3a470@Class_10B3A470@@QAEPAV1@XZ
Class_10B3A470* Class_10B3A470::FUN_10b3a470()
{
    Unknown00 = 0;
    Unknown01 = 0;
    Unknown04 = 0.25f;
    Unknown08 = -1.0f;
    Unknown18 = 0;
    Unknown1C = 7;
    Unknown20 = 7;
    Unknown24 = 0;
    Unknown28 = 0;
    return this;
}

// FUNCTION: 0x10B3AC50 ?FUN_10b3ac50@Class_10B3AC50@@QAEXPAX@Z
void Class_10B3AC50::FUN_10b3ac50(void* p1)
{
    *(void**)this = p1;
}

// FUNCTION: 0x10B3AC60 ?FUN_10b3ac60@@YAPAUStatic_10B3AC60@@XZ
Static_10B3AC60* FUN_10b3ac60()
{
    static Static_10B3AC60 Instance;
    return &Instance;
}

// FUNCTION: 0x10B3AD70 ?FUN_10b3ad70@@YAMXZ
float FUN_10b3ad70()
{
    return DAT_10e7e4b4;
}

// FUNCTION: 0x10B3AD80 ?FUN_10b3ad80@@YAMXZ
float FUN_10b3ad80()
{
    return DAT_10e7e4b8;
}

// FUNCTION: 0x10B3ADC0 ?FUN_10b3adc0@Class_10B3ADC0@@QAEXPAVObject_10B3ADC0@@@Z
void Class_10B3ADC0::FUN_10b3adc0(Object_10B3ADC0* param)
{
    param->Field450 |= 0x4;
}

// FUNCTION: 0x10B3D210 ?FUN_10b3d210@@YAHXZ
int FUN_10b3d210()
{
    return 0xf;
}

// FUNCTION: 0x10B3D260 ?FUN_10b3d260@@YAHXZ
int FUN_10b3d260()
{
    return 0x11;
}

// FUNCTION: 0x10B3D290 ?FUN_10b3d290@@YAHXZ
int FUN_10b3d290()
{
    return 0x12;
}

// FUNCTION: 0x10B3D2C0 ?FUN_10b3d2c0@@YAHXZ
int FUN_10b3d2c0()
{
    return 0x17;
}

// FUNCTION: 0x10B3D310 ?FUN_10b3d310@@YAHXZ
int FUN_10b3d310()
{
    return 0x1e;
}

// FUNCTION: 0x10B3D340 ?FUN_10b3d340@@YAHXZ
int FUN_10b3d340()
{
    return 0x19;
}

// FUNCTION: 0x10B3D370 ?FUN_10b3d370@@YAHXZ
int FUN_10b3d370()
{
    return 0x1a;
}

// FUNCTION: 0x10B3D3C0 ?FUN_10b3d3c0@@YAHXZ
int FUN_10b3d3c0()
{
    return 0x14;
}

// FUNCTION: 0x10B3D3F0 ?FUN_10b3d3f0@@YAHXZ
int FUN_10b3d3f0()
{
    return 0x15;
}

// FUNCTION: 0x10B3D420 ?FUN_10b3d420@@YAHXZ
int FUN_10b3d420()
{
    return 0x16;
}

// FUNCTION: 0x10B3D450 ?FUN_10b3d450@@YAHXZ
int FUN_10b3d450()
{
    return 0x1b;
}

// FUNCTION: 0x10B3D480 ?FUN_10b3d480@@YAHXZ
int FUN_10b3d480()
{
    return 0x1c;
}

// FUNCTION: 0x10B3D4B0 ?FUN_10b3d4b0@@YAHXZ
int FUN_10b3d4b0()
{
    return 0x1d;
}

// FUNCTION: 0x10B3D4E0 ?FUN_10b3d4e0@@YAHXZ
int FUN_10b3d4e0()
{
    return 0x20;
}

// FUNCTION: 0x10B3E210 ?FUN_10b3e210@@YGXPAUInfo_10B3E210@@@Z
void __stdcall FUN_10b3e210(Info_10B3E210* Out)
{
    Out->Unknown00 = 0x3f9c;
    Out->Unknown04 = 0x4000;
    Out->Unknown08 = 0x4000;
    Out->Unknown0C = 0x1ccc;
    Out->Unknown10 = 0x1ccc;
}

// FUNCTION: 0x10B405A0 ?FUN_10b405a0@@YAXXZ
void FUN_10b405a0()
{
    FUN_10a58e50();
}

// FUNCTION: 0x10B40610 ?FUN_10b40610@@YAXXZ
void FUN_10b40610()
{
    FUN_10a51620();
}

// FUNCTION: 0x10B40780 ??0Class_10E7FED0@@QAE@XZ
Class_10E7FED0::Class_10E7FED0()
{
}

// FUNCTION: 0x10B40810 ?FUN_10b40810@@YAXXZ
void FUN_10b40810()
{
    FUN_10b2bd00();
}

// FUNCTION: 0x10B408A0 ?FUN_10b408a0@@YAPAUClass_10E7FB00@@XZ
Class_10E7FB00* FUN_10b408a0()
{
    static Class_10E7FB00 Instance;
    return &Instance;
}

// FUNCTION: 0x10B40A40 ??_GClass_10E7FED0@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B40780's definition in this unit.

// FUNCTION: 0x10B40A80 ?FUN_10b40a80@@YAXXZ
void FUN_10b40a80()
{
    FUN_10b40820();
}

// FUNCTION: 0x10B42340 ?FUN_10b42340@Class_10B42340@@QAEPAV1@HH@Z
Class_10B42340* Class_10B42340::FUN_10b42340(int A, int B)
{
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown00 = A;
    Unknown04 = B;
    Unknown14 = 0.03f;
    return this;
}

// FUNCTION: 0x10B42640 ?FUN_10b42640@Class_10B42640@@QAEXXZ
void Class_10B42640::FUN_10b42640()
{
    Field1C = 0;
}

// FUNCTION: 0x10B429A0 ?FUN_10b429a0@Class_10B429A0@@QAEXH@Z
void Class_10B429A0::FUN_10b429a0(int param)
{
    Field120 = param;
}

// FUNCTION: 0x10B43D40 ?FUN_10b43d40@Class_10B43D40@@QAEXPAX@Z
void Class_10B43D40::FUN_10b43d40(void* p1)
{
    Field150 = p1;
}

// FUNCTION: 0x10B43D50 ?FUN_10b43d50@Class_10B43D50@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10B43D50::FUN_10b43d50()
{
    return Class_109081E0(DAT_10e80e74);
}

// FUNCTION: 0x10B460F0 ??0Class_10E81300@@QAE@XZ
Class_10E81300::Class_10E81300()
{
    Unknown120 = 0;
    Unknown124 = 0;
    Unknown128 = 0;
}

// FUNCTION: 0x10B461A0 ??_GClass_10E81300@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B460F0's definition in this unit.

// FUNCTION: 0x10B461C0 ?FUN_10b461c0@@YAXXZ
void FUN_10b461c0()
{
    FUN_10a53400();
}
