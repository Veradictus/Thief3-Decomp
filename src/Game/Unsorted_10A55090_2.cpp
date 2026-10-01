// Game/Unsorted_10A55090_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A56170 {
    char Unknown00[0x1a4];
    unsigned char Field1A4;
public:
    void FUN_10a56170(unsigned char p1);
};

class Class_10A56AA0 {
    char Unknown00[0x13c];
    float Field13C;
public:
    float FUN_10a56aa0();
};

class Class_10A56AD0
{
public:
    char Unknown00[0x17c];
    int Field17c;
    int FUN_10a56ad0();
};

class Class_10A56B00
{
public:
    char Unknown00[0x180];
    int Field180;
    int FUN_10a56b00();
};

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

class Class_10A56B70
{
public:
    Class_10AF8250 FUN_10a56b70();

    char Unknown00[0x158];
    Class_10AF8250 Unknown158;
};

class Class_10a56bc0
{
public:
    char Unknown00[0x154];
    int Unknown154;

    int FUN_10a56bc0();
};

class Class_10a56c30
{
public:
    char Unknown00[0x190];
    int Unknown190;

    int FUN_10a56c30();
};

class Class_10A56C40 {
    char Unknown00[0x190];
    int Field190;
public:
    void FUN_10a56c40(int p1);
};

void FUN_10a58910();

void FUN_10a581b0();

extern void* DAT_10e68f9c[];

extern void* DAT_10e68f94[];

class Class_10E68F9C
{
public:
    Class_10E68F9C* FUN_10a58420();

    void** Unknown00;        // +0x00: DAT_10e68f9c
    float Unknown04;
    int Unknown08;
    void** Unknown0C;        // +0x0c: DAT_10e68f94
    char Unknown10[0x3C];
    float Unknown4C;
};

class Class_10a58470
{
public:
    char Unknown00[0x40];
    unsigned char Unknown40;

    void FUN_10a58470();
};

extern void* DAT_10e68f74[];

class Class_10A58510
{
public:
    void* Field00;
public:
    void FUN_10a58510();
};

extern void* DAT_10e69038[];

class Class_10A589A0
{
public:
    void* Field00;
public:
    void FUN_10a589a0();
};

extern float DAT_10eafbdc;

class Class_10A5B490 {
public:
    char Unknown00[0x13c];
    int Field13c;
    void FUN_10a5b490(int param);
};

extern void* DAT_10e696a8[];

void FUN_10a663b0();

class Class_10A5D420
{
public:
    void* Field00;
public:
    void FUN_10a5d420();
};

class Object_10A626F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
};

class Class_10A626F0
{
public:
    void FUN_10a626f0();
    void FUN_10a64d70();

    char Unknown00[0x1D4];
    Object_10A626F0* Unknown1D4;
    int Unknown1D8;
};

class Class_10A62BC0
{
public:
    char Unknown00[0x1d4];
    int Field1d4;
public:
    int FUN_10a62bc0();
};

struct Base_10A62CB0
{
    int Unknown04;
    int Unknown08;
    int Unknown0C;

    Base_10A62CB0()
    {
        Unknown04 = 0;
        Unknown08 = 0;
        Unknown0C = 0;
    }
};

class Class_10E6AC50 : public Base_10A62CB0
{
public:
    Class_10E6AC50();

    virtual ~Class_10E6AC50();

    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10E6AC98
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual Class_1090A780 FUN_10a63210();

    char Unknown04[0x10];
    Class_1090A780 Unknown14;
};

class Class_10A64CD0
{
public:
    Class_10A64CD0* FUN_10a64cd0();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    bool Unknown20;
    bool Unknown21;
    bool Unknown22;
};

class Class_10A64F10 {
public:
    char Unknown00[0x14c];
    unsigned char Field150;
    unsigned char Field151;
    virtual void FUN_10a64f10();
};

void FUN_10aa7100();

// FUNCTION: 0x10A56170 ?FUN_10a56170@Class_10A56170@@QAEXE@Z
void Class_10A56170::FUN_10a56170(unsigned char p1)
{
    Field1A4 = p1;
}

// FUNCTION: 0x10A56AA0 ?FUN_10a56aa0@Class_10A56AA0@@QAEMXZ
float Class_10A56AA0::FUN_10a56aa0()
{
    return Field13C;
}

// FUNCTION: 0x10A56AD0 ?FUN_10a56ad0@Class_10A56AD0@@QAEHXZ
int Class_10A56AD0::FUN_10a56ad0()
{
    return Field17c;
}

// FUNCTION: 0x10A56B00 ?FUN_10a56b00@Class_10A56B00@@QAEHXZ
int Class_10A56B00::FUN_10a56b00()
{
    return Field180;
}

// FUNCTION: 0x10A56B70 ?FUN_10a56b70@Class_10A56B70@@QAE?AVClass_10AF8250@@XZ
Class_10AF8250 Class_10A56B70::FUN_10a56b70()
{
    return Class_10AF8250(Unknown158);
}

// FUNCTION: 0x10A56BC0 ?FUN_10a56bc0@Class_10a56bc0@@QAEHXZ
int Class_10a56bc0::FUN_10a56bc0()
{
    return Unknown154;
}

// FUNCTION: 0x10A56C30 ?FUN_10a56c30@Class_10a56c30@@QAEHXZ
int Class_10a56c30::FUN_10a56c30()
{
    return Unknown190;
}

// FUNCTION: 0x10A56C40 ?FUN_10a56c40@Class_10A56C40@@QAEXH@Z
void Class_10A56C40::FUN_10a56c40(int p1)
{
    Field190 = p1;
}

// FUNCTION: 0x10A57970 ?FUN_10a57970@@YAXXZ
void FUN_10a57970()
{
    FUN_10a58910();
}

// FUNCTION: 0x10A58320 ?FUN_10a58320@@YAXXZ
void FUN_10a58320()
{
    FUN_10a581b0();
}

// FUNCTION: 0x10A58420 ?FUN_10a58420@Class_10E68F9C@@QAEPAV1@XZ
Class_10E68F9C* Class_10E68F9C::FUN_10a58420()
{
    Unknown04 = 1.0f;
    Unknown08 = 0;
    Unknown00 = DAT_10e68f9c;
    Unknown0C = DAT_10e68f94;
    Unknown4C = 32767.0f;
    return this;
}

// FUNCTION: 0x10A58470 ?FUN_10a58470@Class_10a58470@@QAEXXZ
void Class_10a58470::FUN_10a58470() {
    Unknown40 = 1;
}

// FUNCTION: 0x10A58510 ?FUN_10a58510@Class_10A58510@@QAEXXZ
void Class_10A58510::FUN_10a58510()
{
    Field00 = (void*)DAT_10e68f74;
}

// FUNCTION: 0x10A589A0 ?FUN_10a589a0@Class_10A589A0@@QAEXXZ
void Class_10A589A0::FUN_10a589a0()
{
    Field00 = (void*)DAT_10e69038;
}

// FUNCTION: 0x10A589B0 ?FUN_10a589b0@@YAMXZ
float FUN_10a589b0()
{
    return DAT_10eafbdc;
}

// FUNCTION: 0x10A5B490 ?FUN_10a5b490@Class_10A5B490@@QAEXH@Z
void Class_10A5B490::FUN_10a5b490(int param)
{
    Field13c = param;
}

// FUNCTION: 0x10A5D420 ?FUN_10a5d420@Class_10A5D420@@QAEXXZ
void Class_10A5D420::FUN_10a5d420()
{
    Field00 = (void*)DAT_10e696a8;
    FUN_10a663b0();
}

// FUNCTION: 0x10A626F0 ?FUN_10a626f0@Class_10A626F0@@QAEXXZ
void Class_10A626F0::FUN_10a626f0()
{
    Unknown1D8 = 0;
    Unknown1D4->Virtual9();
    FUN_10a64d70();
}

// FUNCTION: 0x10A62BC0 ?FUN_10a62bc0@Class_10A62BC0@@QAEHXZ
int Class_10A62BC0::FUN_10a62bc0()
{
    return Field1d4;
}

// FUNCTION: 0x10A62CB0 ??0Class_10E6AC50@@QAE@XZ
Class_10E6AC50::Class_10E6AC50()
{
    Unknown10 = -1;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
}

// FUNCTION: 0x10A63210 ?FUN_10a63210@Class_10E6AC98@@UAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10E6AC98::FUN_10a63210()
{
    return Class_1090A780(Unknown14);
}

// FUNCTION: 0x10A63480 ??_GClass_10E6AC50@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10A62CB0's definition in this unit.

// FUNCTION: 0x10A64CD0 ?FUN_10a64cd0@Class_10A64CD0@@QAEPAV1@XZ
Class_10A64CD0* Class_10A64CD0::FUN_10a64cd0()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = false;
    Unknown21 = false;
    Unknown22 = false;
    return this;
}

// FUNCTION: 0x10A64F10 ?FUN_10a64f10@Class_10A64F10@@UAEXXZ
void Class_10A64F10::FUN_10a64f10()
{
    Field150 = 1;
    Field151 = 0;
    FUN_10aa7100();
}
