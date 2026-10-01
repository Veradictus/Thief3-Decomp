// Game/Unsorted_10C0CED0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47600[];

extern int DAT_10ff6608;

int FUN_10b953b0(const char* Name);

void FUN_10b969a0();

class Class_10E8C378
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
    virtual void Virtual13();
    virtual int FUN_10c12880();
};

extern int DAT_10ff6610;

int FUN_10b95550(const char* Name);

void FUN_10b96bc0();

class Class_10E8C42C
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
    virtual void Virtual13();
    virtual int FUN_10c128b0();
};

extern int DAT_10ff660c;

int FUN_10b95480(const char* Name);

void FUN_10b96ab0();

class Class_10E8C3B4
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
    virtual void Virtual13();
    virtual int FUN_10c128e0();
};

extern int DAT_10ff6614;

int FUN_10b95620(const char* Name);

void FUN_10b96cd0();

class Class_10E8C3F0
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
    virtual void Virtual13();
    virtual int FUN_10c12910();
};

extern int DAT_10ff6618;

int FUN_10b956f0(const char* Name);

void FUN_10b96de0();

class Class_10E8C468
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
    virtual void Virtual13();
    virtual int FUN_10c12940();
};

class Class_10E8C4A4
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
    virtual bool FUN_10c129b0();

    char Unknown04[4];
    int Unknown08;
};

extern void* DAT_10e984bc[];

class Class_10E984BC {
public:
    Class_10E984BC();

    void** Unknown00;
    int Unknown04;
};

extern void* DAT_10e984f4[];

class Class_10e984f4
{
public:
    void* Unknown00;
    int Unknown04;
    Class_10e984f4* FUN_10c12a90();
};

class Class_10E98530
{
public:
    Class_10E98530();

    virtual ~Class_10E98530();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

// FUNCTION: 0x10C12880 ?FUN_10c12880@Class_10E8C378@@UAEHXZ
int Class_10E8C378::FUN_10c12880()
{
    if (DAT_10ff6608 == 0)
    {
        DAT_10ff6608 = FUN_10b953b0(DAT_10e47600);
        FUN_10b969a0();
    }
    return DAT_10ff6608;
}

// FUNCTION: 0x10C128B0 ?FUN_10c128b0@Class_10E8C42C@@UAEHXZ
int Class_10E8C42C::FUN_10c128b0()
{
    if (DAT_10ff6610 == 0)
    {
        DAT_10ff6610 = FUN_10b95550(DAT_10e47600);
        FUN_10b96bc0();
    }
    return DAT_10ff6610;
}

// FUNCTION: 0x10C128E0 ?FUN_10c128e0@Class_10E8C3B4@@UAEHXZ
int Class_10E8C3B4::FUN_10c128e0()
{
    if (DAT_10ff660c == 0)
    {
        DAT_10ff660c = FUN_10b95480(DAT_10e47600);
        FUN_10b96ab0();
    }
    return DAT_10ff660c;
}

// FUNCTION: 0x10C12910 ?FUN_10c12910@Class_10E8C3F0@@UAEHXZ
int Class_10E8C3F0::FUN_10c12910()
{
    if (DAT_10ff6614 == 0)
    {
        DAT_10ff6614 = FUN_10b95620(DAT_10e47600);
        FUN_10b96cd0();
    }
    return DAT_10ff6614;
}

// FUNCTION: 0x10C12940 ?FUN_10c12940@Class_10E8C468@@UAEHXZ
int Class_10E8C468::FUN_10c12940()
{
    if (DAT_10ff6618 == 0)
    {
        DAT_10ff6618 = FUN_10b956f0(DAT_10e47600);
        FUN_10b96de0();
    }
    return DAT_10ff6618;
}

// FUNCTION: 0x10C129B0 ?FUN_10c129b0@Class_10E8C4A4@@UAE_NXZ
bool Class_10E8C4A4::FUN_10c129b0()
{
    return Unknown08 != 0;
}

// FUNCTION: 0x10C129F0 ??0Class_10E984BC@@QAE@XZ
Class_10E984BC::Class_10E984BC()
{
    Unknown00 = DAT_10e984bc;
    Unknown04 = 0;
}

// FUNCTION: 0x10C12A90 ?FUN_10c12a90@Class_10e984f4@@QAEPAV1@XZ
Class_10e984f4* Class_10e984f4::FUN_10c12a90()
{
    Unknown00 = DAT_10e984f4;
    Unknown04 = 0;
    return this;
}

// FUNCTION: 0x10C12B30 ??0Class_10E98530@@QAE@XZ
Class_10E98530::Class_10E98530()
{
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
}

// FUNCTION: 0x10C132A0 ??_GClass_10E98530@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10C12B30's definition in this unit.
