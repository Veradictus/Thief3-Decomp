// Game/Unsorted_10BE9BD0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BECE80_Target {
public:
    char Unknown00[0x1EC];
    unsigned char Unknown1EC;
};

class Class_10E92730 {
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
    virtual bool FUN_10bece80();

    Class_10BECE80_Target* Unknown04;
};

class Class_10E59F90
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
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void FUN_10becee0(int p1);

    char Unknown04[0x74];
    int Unknown78;
};

void __stdcall FUN_109e3c90(int);

class Class_10E975A0
{
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
    virtual void Virtual7() = 0;
    virtual void Virtual8() = 0;
    virtual void Virtual9() = 0;
    virtual void Virtual10() = 0;
    virtual void Virtual11() = 0;
    virtual void Virtual12() = 0;
    virtual void Virtual13() = 0;
    virtual void Virtual14() = 0;
    virtual void Virtual15() = 0;
    virtual void Virtual16() = 0;
    virtual void Virtual17() = 0;
    virtual void Virtual18() = 0;
    virtual void Virtual19() = 0;
    virtual void Virtual20() = 0;
    virtual void FUN_10becef0();
};

// FUNCTION: 0x10BECE80 ?FUN_10bece80@Class_10E92730@@UAE_NXZ
bool Class_10E92730::FUN_10bece80()
{
    return Unknown04->Unknown1EC == 0;
}

// FUNCTION: 0x10BECEE0 ?FUN_10becee0@Class_10E59F90@@UAEXH@Z
void Class_10E59F90::FUN_10becee0(int p1)
{
    Unknown78 = p1;
}

// FUNCTION: 0x10BECEF0 ?FUN_10becef0@Class_10E975A0@@UAEXXZ
void Class_10E975A0::FUN_10becef0()
{
    FUN_109e3c90(0);
}
