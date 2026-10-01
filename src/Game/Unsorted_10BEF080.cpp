// Game/Unsorted_10BEF080.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10c00480();

class Class_10BBB8B0
{
public:
    bool FUN_10bbb8b0();
};

class Class_10BEF080
{
public:
    void FUN_10bef080();

    char Unknown00[4];
    Class_10BBB8B0* Unknown04;
    char Unknown08[0x12C];
    int Unknown134;
    char Unknown138[0xE8];
    float Unknown220;
};

class Class_10BB8300
{
public:
    void FUN_10bb8300();
};

class Class_10BEF0F0_Member
{
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
};

class Class_10E97720
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10bef0f0();

    Class_10BB8300* Unknown04;
    char Unknown08[0x38];
    Class_10BEF0F0_Member* Unknown40;
    char Unknown44[0x130];
    char Unknown174;
    char Unknown175[0xE7];
    int Unknown25C;
};

// FUNCTION: 0x10BEF080 ?FUN_10bef080@Class_10BEF080@@QAEXXZ
void Class_10BEF080::FUN_10bef080()
{
    Unknown134 = Unknown04->FUN_10bbb8b0() ? 1 : 2;
    Unknown220 = FUN_10c00480() + 1.0;
}

// FUNCTION: 0x10BEF0F0 ?FUN_10bef0f0@Class_10E97720@@UAEXXZ
void Class_10E97720::FUN_10bef0f0()
{
    if (Unknown25C)
    {
        Unknown04->FUN_10bb8300();
        return;
    }
    if (!Unknown174)
    {
        Class_10BEF0F0_Member* P = Unknown40;
        if (P)
            P->Virtual6();
    }
}
