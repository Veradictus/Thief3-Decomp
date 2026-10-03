// Game/Unsorted_10BDBD50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

class Class_10AAF570
{
public:
    int FUN_10aaf570();
};

class Class_10BBDB40 : public Class_10AAF570
{
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510();
};

struct Struct_10BDC290
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10FF667C
{
public:
    char Unknown00[0xA8];
    float UnknownA8;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10BDC290
{
public:
    float FUN_10bdc290();

    char Unknown00[4];
    Struct_10BDC290* Unknown04;
};

class Class_10971570
{
public:
    void FUN_10971570(int A, bool* B);
};

class Object_10BDC830
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
    virtual void Virtual87();
    virtual void Virtual88();
    virtual void Virtual89();
    virtual void Virtual90();
    virtual void Virtual91();
    virtual void Virtual92();
    virtual void Virtual93();
    virtual void Virtual94();
    virtual void Virtual95();
    virtual void Virtual96();
    virtual void Virtual97();
    virtual Class_10971570* Virtual98();
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10BDC830
{
    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

class Class_10E94C58
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
    virtual void FUN_10bdc830(int A);

    Struct_10BDC830* Unknown04;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);

    char Unknown04[8];
    int Unknown0C;
};

FArchive& FUN_10b052a0(FArchive& Ar, void* V);

class Class_10E8BE68
{
public:
    virtual void FUN_10bca010(FArchive& Ar);
};

class Class_10E94100 : public Class_10E8BE68
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
    virtual void FUN_10bdbd70(FArchive& Ar);

    char Unknown04[0x3C];
    int Unknown40;
    int Unknown44;
    int Unknown48[3];
};

// FUNCTION: 0x10BDBD70 ?FUN_10bdbd70@Class_10E94100@@UAEXAAVFArchive@@@Z
void Class_10E94100::FUN_10bdbd70(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    if (Ar.Unknown0C >= 0x60)
    {
        Ar.Serialize(&Unknown40, 4);
        Ar.Serialize(&Unknown44, 4);
        FUN_10b052a0(Ar, Unknown48);
    }
}

// FUNCTION: 0x10BDC290 ?FUN_10bdc290@Class_10BDC290@@QAEMXZ
float Class_10BDC290::FUN_10bdc290()
{
    float Value = 0.0f;
    Class_10DBD510* Props = Unknown04->Unknown08;
    ((Class_1098E330*)Props->FUN_10dbd510()->FUN_10aaf570())->FUN_1098e330(0x1007be, (int*)&Value);
    return Value * DAT_10ff667c->UnknownA8;
}

// FUNCTION: 0x10BDC830 ?FUN_10bdc830@Class_10E94C58@@UAEXH@Z
void Class_10E94C58::FUN_10bdc830(int A)
{
    Class_10971570* Obj = ((Object_10BDC830*)Unknown04->Unknown08->FUN_10c7d570())->Virtual98();
    bool Flag = false;
    Obj->FUN_10971570(0x20000bd, &Flag);
}
