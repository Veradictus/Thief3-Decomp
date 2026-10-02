// Game/Unsorted_10BE1F00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

class Class_10E8BE68
{
public:
    virtual void FUN_10bca010(FArchive& Ar);
};

class Class_10E959B0 : public Class_10E8BE68
{
public:
    virtual void FUN_10be20e0(FArchive& Ar);

    char Unknown04[0x3C];
    char Unknown40;
};

class Class_10E94578 : public Class_10E8BE68
{
public:
    void FUN_10bc5b50();
};

class Class_10FF667C_Unknown18
{
public:
    virtual void Virtual0();
    virtual void Virtual1(FArchive& Ar, int* Value);
};

class Class_10FF667C
{
public:
    char Unknown00[0x18];
    Class_10FF667C_Unknown18* Unknown18;
};

extern Class_10FF667C* DAT_10ff667c;

extern float DAT_10e49684;

double FUN_10c00480();

class Class_10E95898 : public Class_10E94578
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void FUN_10be1c00();
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
    virtual void FUN_10be2090(FArchive& Ar);

    char Unknown04[0x3C];
    float Unknown40;
    int Unknown44;
    unsigned char Unknown48;
    unsigned char Unknown49;
};

// FUNCTION: 0x10BE2090 ?FUN_10be2090@Class_10E95898@@UAEXAAVFArchive@@@Z
void Class_10E95898::FUN_10be2090(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    Ar.Serialize(&Unknown40, 4);
    DAT_10ff667c->Unknown18->Virtual1(Ar, &Unknown44);
    Ar.Serialize(&Unknown48, 1);
    Ar.Serialize(&Unknown49, 1);
}

// FUNCTION: 0x10BE20E0 ?FUN_10be20e0@Class_10E959B0@@UAEXAAVFArchive@@@Z
void Class_10E959B0::FUN_10be20e0(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    Ar.Serialize(&Unknown40, 1);
}
