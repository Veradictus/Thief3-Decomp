// Game/Unsorted_10BE9D40_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class APawn
{
public:
    void FUN_10a6ea30(int Flags, int Value);
};

struct Struct_10BE9AC0
{
    char Unknown00[4];
    APawn* Unknown04;
};

class Class_10BB86B0
{
public:
    void FUN_10bb86b0(float A);
};

class Class_Field04 : public Class_10BB86B0
{
public:
    void FUN_10bb83e0();
};

class Class_10E970F0
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
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void FUN_10beae90();

    Class_Field04* Unknown04;
    char Unknown08[0x58];
    Struct_10BE9AC0* Unknown60;
};

// FUNCTION: 0x10BEAE90 ?FUN_10beae90@Class_10E970F0@@UAEXXZ
void Class_10E970F0::FUN_10beae90()
{
    Unknown04->FUN_10bb83e0();
    if (Unknown60)
    {
        if (Unknown60->Unknown04)
            Unknown60->Unknown04->FUN_10a6ea30(0x800709, 0);
        delete Unknown60;
        Unknown60 = 0;
    }
    Unknown60 = 0;
    Unknown04->FUN_10bb86b0(0.5f);
}
