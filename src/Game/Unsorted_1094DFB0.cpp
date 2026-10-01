// Game/Unsorted_1094DFB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10919190
{
    int Unknown00;
};

void FUN_10919190(Struct_10919190* P);

class Class_1094E050
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
    virtual void Virtual8(int A);
};

extern int DAT_10f2c720;

class Class_10E4AB88
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
    virtual void FUN_1094e050();

    Struct_10919190 Unknown04;
    char Unknown08[0xE0];
    Class_1094E050* Unknown0E8[1];
};

class Class_1094DFB0_Slot
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
};

class Class_1094DFB0
{
public:
    void FUN_1094dfb0();

    char Unknown00[0xE8];
    Class_1094DFB0_Slot* Unknown0E8[1];
};

class Class_1094DFD0_Slot
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
};

class Class_1094DFD0
{
public:
    void FUN_1094dfd0();

    char Unknown00[0x114];
    Class_1094DFD0_Slot* Unknown114[1];
};

// FUNCTION: 0x1094DFB0 ?FUN_1094dfb0@Class_1094DFB0@@QAEXXZ
void Class_1094DFB0::FUN_1094dfb0()
{
    if (Unknown0E8[DAT_10f2c720])
        Unknown0E8[DAT_10f2c720]->Virtual7();
}

// FUNCTION: 0x1094DFD0 ?FUN_1094dfd0@Class_1094DFD0@@QAEXXZ
void Class_1094DFD0::FUN_1094dfd0()
{
    if (Unknown114[DAT_10f2c720])
        Unknown114[DAT_10f2c720]->Virtual7();
}

// FUNCTION: 0x1094E050 ?FUN_1094e050@Class_10E4AB88@@UAEXXZ
void Class_10E4AB88::FUN_1094e050()
{
    FUN_10919190(&Unknown04);
    Unknown0E8[DAT_10f2c720]->Virtual8(0);
}
