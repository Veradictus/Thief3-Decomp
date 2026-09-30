// Game/Unsorted_10A46070_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10a46380
{
public:
    char Unknown00[0x20c];
    int Unknown20c;

    int FUN_10a46380();
};

class Class_10a46e00
{
public:
    char Unknown00[0x1f8];
    int Unknown1f8;

    int FUN_10a46e00();
};

void FUN_10a46c10();

void FUN_10a46c70();

void FUN_10a46cd0();

void FUN_10991270();

void FUN_10a47530();

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

extern int DAT_10f3a084;

class Class_10E67938
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a4c4d0(int A);
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14(int* Out, int A);
};

extern void* DAT_10e6798c[];

class Class_10E6798C
{
public:
    Class_10E6798C* FUN_10a4d310();

    void** Unknown00;
    char Unknown04[0x24];
    int Unknown28;
    int Unknown2C;
    int Unknown30;
    int Unknown34;
    int Unknown38;
    int Unknown3C;
    int Unknown40;
    int Unknown44;
    int Unknown48;
};

class Class_10A4D340
{
public:
    void* Field00;
    void FUN_10a4d340();
};

extern void* DAT_10e679bc[];

class Class_10A4D400
{
public:
    void* Field00;
    void FUN_10a4d400();
};

void FUN_10a4e3d0();

class InnerClass_10A4EB40
{
public:
    void FUN_10a4e3d0();
};

class Class_10A4EB40
{
public:
    char Unknown00[0x1c];
    InnerClass_10A4EB40 Field1c;
    void FUN_10a4eb40();
};

void FUN_10a4e580();

class InnerClass_10A4EB50
{
public:
    void FUN_10a4e580();
};

class Class_10A4EB50
{
public:
    char Unknown00[0x1c];
    InnerClass_10A4EB50 Field1c;
    void FUN_10a4eb50();
};

class Class_10A50750
{
public:
    Class_10A50750* FUN_10a50750();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    float Unknown20;
};

void FUN_10a51ab0();

extern void* DAT_10e67df0;

class Class_10a51d60
{
public:
    void FUN_10a51d60();
};

class Class_10A52110
{
public:
    bool FUN_10a52110();

    char Unknown00[0x10C];
    void* Unknown10C;
    int Unknown110;
    int Unknown114;
};

class Class_10a52460
{
public:
    char Unknown00[0x58];
    void* Unknown58;

    void* FUN_10a52460();
};

class Class_10a53250
{
public:
    char Unknown00[0x20];
    unsigned char Unknown20;

    void FUN_10a53250();
};

extern const char DAT_10e47660[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10A53BD0
{
public:
    Class_109081E0 FUN_10a53bd0(int A);
};

extern void* DAT_10e67fb8;

class Class_10a53d80
{
public:
    void FUN_10a53d80();
};

class Class_10A54CC0
{
public:
    char Unknown00[0x120];
    unsigned char Field120;
    unsigned char FUN_10a54cc0();
};

class Class_1090A780
{
public:
    Class_1090A780() : Unknown00(0) {}
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual void Virtual0();

    char Unknown04[0x114];
};

class Class_10E682F0 : public Class_10E67FD0
{
public:
    Class_10E682F0();

    virtual void Virtual0();

    int Unknown118;
    Class_1090A780 Unknown11C;
    char Unknown120;
    char Unknown121;
};

class Class_10A55080 {
public:
    char Unknown00[0x119];
    unsigned char Field119;
    void FUN_10a55080(unsigned char param);
};

// FUNCTION: 0x10A46380 ?FUN_10a46380@Class_10a46380@@QAEHXZ
int Class_10a46380::FUN_10a46380()
{
    return Unknown20c;
}

// FUNCTION: 0x10A47040 ?FUN_10a47040@@YAXXZ
void FUN_10a47040()
{
    FUN_10991270();
}

// FUNCTION: 0x10A47590 ?FUN_10a47590@@YAXXZ
void FUN_10a47590()
{
    FUN_10a47530();
}

// FUNCTION: 0x10A48B10 ?FUN_10a48b10@@YAHPAVClass_1098E330@@@Z
int FUN_10a48b10(Class_1098E330* Obj)
{
    int Value = 0;
    Obj->FUN_1098e330(0x4002002b, &Value);
    return Value;
}

// FUNCTION: 0x10A4C4D0 ?FUN_10a4c4d0@Class_10E67938@@UAE_NH@Z
bool Class_10E67938::FUN_10a4c4d0(int A)
{
    Virtual14(&A, A);
    return A != DAT_10f3a084;
}

// FUNCTION: 0x10A4D310 ?FUN_10a4d310@Class_10E6798C@@QAEPAV1@XZ
Class_10E6798C* Class_10E6798C::FUN_10a4d310()
{
    Unknown00 = DAT_10e6798c;
    Unknown28 = 0;
    Unknown44 = 0;
    Unknown48 = 0;
    Unknown40 = 0;
    Unknown3C = 0;
    Unknown38 = 0;
    Unknown34 = 0;
    Unknown30 = 0;
    Unknown2C = 0;
    return this;
}

// FUNCTION: 0x10A4D340 ?FUN_10a4d340@Class_10A4D340@@QAEXXZ
void Class_10A4D340::FUN_10a4d340()
{
    Field00 = (void*)DAT_10e6798c;
}

// FUNCTION: 0x10A4D400 ?FUN_10a4d400@Class_10A4D400@@QAEXXZ
void Class_10A4D400::FUN_10a4d400()
{
    Field00 = (void*)DAT_10e679bc;
}

// FUNCTION: 0x10A4EB40 ?FUN_10a4eb40@Class_10A4EB40@@QAEXXZ
void Class_10A4EB40::FUN_10a4eb40()
{
    Field1c.FUN_10a4e3d0();
}

// FUNCTION: 0x10A4EB50 ?FUN_10a4eb50@Class_10A4EB50@@QAEXXZ
void Class_10A4EB50::FUN_10a4eb50()
{
    Field1c.FUN_10a4e580();
}

// FUNCTION: 0x10A50750 ?FUN_10a50750@Class_10A50750@@QAEPAV1@XZ
Class_10A50750* Class_10A50750::FUN_10a50750()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = -1.0f;
    Unknown08 = 0;
    return this;
}

// FUNCTION: 0x10A50DE0 ?FUN_10a50de0@@YAXXZ
void FUN_10a50de0()
{
    FUN_10a51ab0();
}

// FUNCTION: 0x10A51D60 ?FUN_10a51d60@Class_10a51d60@@QAEXXZ
void Class_10a51d60::FUN_10a51d60() {
    *(void**)this = &DAT_10e67df0;
}

// FUNCTION: 0x10A52110 ?FUN_10a52110@Class_10A52110@@QAE_NXZ
bool Class_10A52110::FUN_10a52110()
{
    bool HasData = Unknown10C != 0;
    if (HasData)
    {
        Unknown10C = 0;
        Unknown110 = 0;
        Unknown114 = 0;
    }
    return HasData;
}

// FUNCTION: 0x10A52460 ?FUN_10a52460@Class_10a52460@@QAEPAXXZ
void* Class_10a52460::FUN_10a52460() {
    return &Unknown58;
}

// FUNCTION: 0x10A53250 ?FUN_10a53250@Class_10a53250@@QAEXXZ
void Class_10a53250::FUN_10a53250() {
    Unknown20 = 1;
}

// FUNCTION: 0x10A53BD0 ?FUN_10a53bd0@Class_10A53BD0@@QAE?AVClass_109081E0@@H@Z
Class_109081E0 Class_10A53BD0::FUN_10a53bd0(int A)
{
    return Class_109081E0(DAT_10e47660);
}

// FUNCTION: 0x10A53D80 ?FUN_10a53d80@Class_10a53d80@@QAEXXZ
void Class_10a53d80::FUN_10a53d80() {
    *(void**)this = &DAT_10e67fb8;
}

// FUNCTION: 0x10A54CC0 ?FUN_10a54cc0@Class_10A54CC0@@QAEEXZ
unsigned char Class_10A54CC0::FUN_10a54cc0()
{
    return Field120;
}

// FUNCTION: 0x10A54D20 ??0Class_10E682F0@@QAE@XZ
Class_10E682F0::Class_10E682F0() : Unknown118(0), Unknown120(0), Unknown121(1)
{
}

// FUNCTION: 0x10A55080 ?FUN_10a55080@Class_10A55080@@QAEXE@Z
void Class_10A55080::FUN_10a55080(unsigned char param)
{
    Field119 = param;
}
