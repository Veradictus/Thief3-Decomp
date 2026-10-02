// Game/Unsorted_10C06560.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C06F80
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
    virtual int Virtual85();
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

class Class_10C065F0
{
public:
    void FUN_10c065f0(FArchive& Ar);
};

class Class_10C066A0
{
public:
    void FUN_10c066a0(FArchive& Ar);
};

class Class_10E8C008
{
public:
    virtual void FUN_10c06750(FArchive& Ar);

    char Unknown04[0xC];
    Class_10C065F0 Unknown10;
    char Unknown11[0xB];
    Class_10C066A0 Unknown1C;
};

class Class_10963740
{
public:
    Class_10963740* FUN_10963740(int A, int B, int C);

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C06F30
{
public:
    Class_10963740* FUN_10c06f30(Class_10963740* Out, int Index);
    int FUN_10c06d30(int Index, int* B, int* C);
};

// FUNCTION: 0x10C06750 ?FUN_10c06750@Class_10E8C008@@UAEXAAVFArchive@@@Z
void Class_10E8C008::FUN_10c06750(FArchive& Ar)
{
    int Version = 3;
    Ar.Serialize(&Version, 4);
    Unknown10.FUN_10c065f0(Ar);
    Unknown1C.FUN_10c066a0(Ar);
}

// FUNCTION: 0x10C06F30 ?FUN_10c06f30@Class_10C06F30@@QAEPAVClass_10963740@@PAV2@H@Z
Class_10963740* Class_10C06F30::FUN_10c06f30(Class_10963740* Out, int Index)
{
    int X = 0;
    int Y = 0;
    int Z = FUN_10c06d30(Index, &Y, &X);
    Out->FUN_10963740(Z, Y, X);
    return Out;
}

// FUNCTION: 0x10C06F80 ?FUN_10c06f80@@YAHPAVClass_10C06F80@@@Z
int FUN_10c06f80(Class_10C06F80* Obj)
{
    int Value = Obj->Virtual85();
    if (Value == 1 || Value == 2)
        return 0;
    return 1;
}
