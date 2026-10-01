// Game/Unsorted_10C60D80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9CB00
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
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual bool FUN_10c60ff0();

    char Unknown04[0x11A];
    unsigned char Unknown11E;
};

class Class_10C60ED0
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

    bool FUN_10c60ed0();

    char Unknown04[0x118];
    bool Unknown11C;
};

int FUN_10c7fcb0();

class Class_10C60F70
{
public:
    int FUN_10c60f70();

    char Unknown00[0x100];
    int Unknown100;
    char Unknown104[0x10];
    bool Unknown114;
};

// FUNCTION: 0x10C60ED0 ?FUN_10c60ed0@Class_10C60ED0@@QAE_NXZ
bool Class_10C60ED0::FUN_10c60ed0()
{
    Virtual9();
    return Unknown11C;
}

// FUNCTION: 0x10C60F70 ?FUN_10c60f70@Class_10C60F70@@QAEHXZ
int Class_10C60F70::FUN_10c60f70()
{
    if (Unknown100 == 0)
    {
        if (Unknown114)
            return 0x10000;
        return 0;
    }
    if (Unknown114)
        return 0x10000;
    return FUN_10c7fcb0();
}

// FUNCTION: 0x10C60FF0 ?FUN_10c60ff0@Class_10E9CB00@@UAE_NXZ
bool Class_10E9CB00::FUN_10c60ff0()
{
    return Unknown11E == 0;
}
