// Game/Unsorted_10BDB480_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

void FUN_10c11ff0(FArchive& Ar, int* P);

class Class_10E8BE68
{
public:
    virtual void FUN_10bca010(FArchive& Ar);
};

class Class_10E94458 : public Class_10E8BE68
{
public:
    virtual void FUN_10bdb550(FArchive& Ar);

    char Unknown04[0x50];
    int Unknown54;
    int Unknown58;
    int Unknown5C;
};

FArchive& FUN_10b052a0(FArchive& Ar, void* V);

class Class_10E94578 : public Class_10E8BE68
{
public:
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
    virtual void FUN_10bdb5f0(FArchive& Ar);

    char Unknown04[0x50];
    float Unknown54[3];
    int Unknown60;
};

// FUNCTION: 0x10BDB550 ?FUN_10bdb550@Class_10E94458@@UAEXAAVFArchive@@@Z
void Class_10E94458::FUN_10bdb550(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    FUN_10c11ff0(Ar, &Unknown54);
    Ar.Serialize(&Unknown58, 4);
    Ar.Serialize(&Unknown5C, 4);
}

// FUNCTION: 0x10BDB5F0 ?FUN_10bdb5f0@Class_10E94578@@UAEXAAVFArchive@@@Z
void Class_10E94578::FUN_10bdb5f0(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    FUN_10b052a0(Ar, Unknown54);
    Ar.Serialize(&Unknown60, 4);
}
