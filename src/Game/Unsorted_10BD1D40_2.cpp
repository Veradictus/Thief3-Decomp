// Game/Unsorted_10BD1D40_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e932a0[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E932A0 : public Class_10E90D70
{
public:
    Class_10E932A0* FUN_10bd1e00(int A, int B);

    char Unknown40;
};

class Class_10BB8960
{
public:
    void FUN_10bb8960();
};

class Class_10E935F0
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
    virtual void FUN_10bd1e60(int p1);

    Class_10BB8960* Unknown04;
};

extern void* DAT_10e933b8[];

class Class_10E933B8 : public Class_10E90D70
{
public:
    Class_10E933B8* FUN_10bd1e70(int A, int B);

    char Unknown40;
};

extern "C" double cos(double);

class Class_10BBDB40
{
public:
    float FUN_10bbdb40();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

struct Struct_10BD2D10
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10E93878
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
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void Virtual56();
    virtual void Virtual57();
    virtual void Virtual58();
    virtual void Virtual59();
    virtual void Virtual60();
    virtual void Virtual61();
    virtual void Virtual62();
    virtual void Virtual63();
    virtual void Virtual64();
    virtual void Virtual65();
    virtual void Virtual66();
    virtual void Virtual67();
    virtual void Virtual68();
    virtual void Virtual69();
    virtual void Virtual70();
    virtual void Virtual71();
    virtual void Virtual72();
    virtual void Virtual73();
    virtual void Virtual74();
    virtual void Virtual75();
    virtual void Virtual76();
    virtual void Virtual77();
    virtual void Virtual78();
    virtual void Virtual79();
    virtual void Virtual80();
    virtual void Virtual81();
    virtual void Virtual82();
    virtual void Virtual83();
    virtual void Virtual84();
    virtual void Virtual85();
    virtual void Virtual86();
    virtual double FUN_10bd2d10();

    Struct_10BD2D10* Unknown04;
};

// FUNCTION: 0x10BD1E00 ?FUN_10bd1e00@Class_10E932A0@@QAEPAV1@HH@Z
Class_10E932A0* Class_10E932A0::FUN_10bd1e00(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = DAT_10e932a0;
    Unknown40 = 0;
    return this;
}

// FUNCTION: 0x10BD1E60 ?FUN_10bd1e60@Class_10E935F0@@UAEXH@Z
void Class_10E935F0::FUN_10bd1e60(int p1)
{
    Unknown04->FUN_10bb8960();
}

// FUNCTION: 0x10BD1E70 ?FUN_10bd1e70@Class_10E933B8@@QAEPAV1@HH@Z
Class_10E933B8* Class_10E933B8::FUN_10bd1e70(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = 0;
    Unknown00 = DAT_10e933b8;
    return this;
}

// FUNCTION: 0x10BD2D10 ?FUN_10bd2d10@Class_10E93878@@UAENXZ
double Class_10E93878::FUN_10bd2d10()
{
    return cos(Unknown04->Unknown08->FUN_10dbd510(0x100493)->FUN_10bbdb40() * 0.017453292519943295);
}
