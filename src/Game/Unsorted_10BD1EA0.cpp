// Game/Unsorted_10BD1EA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e934d0[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
};

class Class_10E934D0 : public Class_10E90D70
{
public:
    Class_10E934D0* FUN_10bd1ec0(int A, int B);

    char Unknown04[0x3C];
    char Unknown40;
};

class Class_10bb8960_Result
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
};

class Class_10BB8960
{
public:
    Class_10bb8960_Result* FUN_10bb8960();
};

class Class_10E933B8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10bd1ea0();

    Class_10BB8960* Unknown04;
};

// FUNCTION: 0x10BD1EA0 ?FUN_10bd1ea0@Class_10E933B8@@UAEXXZ
void Class_10E933B8::FUN_10bd1ea0()
{
    Unknown04->FUN_10bb8960()->Virtual70();
}

// FUNCTION: 0x10BD1EC0 ?FUN_10bd1ec0@Class_10E934D0@@QAEPAV1@HH@Z
Class_10E934D0* Class_10E934D0::FUN_10bd1ec0(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = 0;
    Unknown00 = DAT_10e934d0;
    return this;
}
