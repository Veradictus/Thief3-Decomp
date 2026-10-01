// Game/Unsorted_10BDB320.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BBDB40
{
public:
    float FUN_10bbdc80();
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

class Class_10BDB320
{
public:
    float FUN_10bdb320();

    char Unknown00[4];
    Struct_10BD2D10* Unknown04;
};

class Class_10BDB340
{
public:
    float FUN_10bdb340();

    char Unknown00[4];
    Struct_10BD2D10* Unknown04;
};

void __stdcall FUN_109e3c90(int A);

class Class_10E94578
{
public:
    virtual void Virtual0();

    void FUN_10bc5b50();
};

class Class_10E94C58 : public Class_10E94578
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
    virtual void FUN_10bdb360(int A);

    char Unknown04[0x50];
    int Unknown54;
};

// FUNCTION: 0x10BDB320 ?FUN_10bdb320@Class_10BDB320@@QAEMXZ
float Class_10BDB320::FUN_10bdb320()
{
    float Value = Unknown04->Unknown08->FUN_10dbd510(0x100615)->FUN_10bbdc80();
    return Value;
}

// FUNCTION: 0x10BDB340 ?FUN_10bdb340@Class_10BDB340@@QAEMXZ
float Class_10BDB340::FUN_10bdb340()
{
    float Value = Unknown04->Unknown08->FUN_10dbd510(0x1006ca)->FUN_10bbdc80();
    return Value;
}

// FUNCTION: 0x10BDB360 ?FUN_10bdb360@Class_10E94C58@@UAEXH@Z
void Class_10E94C58::FUN_10bdb360(int A)
{
    FUN_109e3c90(A);
    if (A == Unknown54)
    {
        Unknown54 = 0;
        FUN_10bc5b50();
    }
}
