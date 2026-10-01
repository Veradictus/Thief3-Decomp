// Game/Unsorted_10B3AC90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10e7e538
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
    virtual void FUN_10b3ad30(int p1, int p2);
};

struct Static_10B18DC0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

Static_10B18DC0* FUN_10b18dc0();

class Class_10E7E538
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
    virtual Static_10B18DC0 FUN_10b3ad40();
};

extern void* DAT_10e7e4e0[];

class Class_10B3ACB0
{
public:
    void* Field00;
    char Unknown04[4];
    int Field08;
    int Field0c;
    Class_10B3ACB0* FUN_10b3acb0();
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    void* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10B3AC90
{
public:
    void* FUN_10b3ac90();

    void* Unknown00;
};

// FUNCTION: 0x10B3AC90 ?FUN_10b3ac90@Class_10B3AC90@@QAEPAXXZ
void* Class_10B3AC90::FUN_10b3ac90()
{
    if (Unknown00 == 0)
    {
        void* Value = DAT_10f35dec->Unknown08;
        if (Value != 0)
            Unknown00 = Value;
    }
    return Unknown00;
}

// FUNCTION: 0x10B3ACB0 ?FUN_10b3acb0@Class_10B3ACB0@@QAEPAV1@XZ
Class_10B3ACB0* Class_10B3ACB0::FUN_10b3acb0()
{
    Field00 = DAT_10e7e4e0;
    Field08 = 0x101;
    Field0c = 0;
    return this;
}

// FUNCTION: 0x10B3AD30 ?FUN_10b3ad30@Class_10e7e538@@UAEXHH@Z
void Class_10e7e538::FUN_10b3ad30(int p1, int p2)
{
    Virtual4();
}

// FUNCTION: 0x10B3AD40 ?FUN_10b3ad40@Class_10E7E538@@UAE?AUStatic_10B18DC0@@XZ
Static_10B18DC0 Class_10E7E538::FUN_10b3ad40()
{
    return *FUN_10b18dc0();
}
