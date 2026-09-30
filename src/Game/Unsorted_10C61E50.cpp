// Game/Unsorted_10C61E50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9cb60;

class Class_10c62a20
{
public:
    void* Unknown00;
    void FUN_10c62a20();
};

class Class_10E5D4B8
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
    virtual void FUN_10c62a30(int param);

    char Unknown04[0x40];
    int Unknown44;
};

class Class_10C62A40
{
public:
    void FUN_10c62a40(unsigned char param);

    char Unknown00[0x20];
    unsigned char Unknown20;
};

extern unsigned char DAT_10ff7115;

// FUNCTION: 0x10C62A20 ?FUN_10c62a20@Class_10c62a20@@QAEXXZ
void Class_10c62a20::FUN_10c62a20()
{
    Unknown00 = &DAT_10e9cb60;
}

// FUNCTION: 0x10C62A30 ?FUN_10c62a30@Class_10E5D4B8@@UAEXH@Z
void Class_10E5D4B8::FUN_10c62a30(int param)
{
    Unknown44 = param;
}

// FUNCTION: 0x10C62A40 ?FUN_10c62a40@Class_10C62A40@@QAEXE@Z
void Class_10C62A40::FUN_10c62a40(unsigned char param)
{
    Unknown20 = param;
}

// FUNCTION: 0x10C62A70 ?FUN_10c62a70@@YAXE@Z
void FUN_10c62a70(unsigned char param)
{
    DAT_10ff7115 = param;
}
