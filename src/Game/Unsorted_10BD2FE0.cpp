// Game/Unsorted_10BD2FE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

FArchive& FUN_10b052a0(FArchive& Ar, void* V);

class Class_10E8BE68
{
public:
    virtual void FUN_10bca010(FArchive& Ar);
};

class Class_10E935F0 : public Class_10E8BE68
{
public:
    virtual void FUN_10bd3090(FArchive& Ar);

    char Unknown04[0x40];
    int Unknown44;
    float Unknown48[3];
};

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BF7F90 : public Class_10AA82D0
{
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    Class_10BF7F90* FUN_10bc4160();
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
    virtual bool Virtual82();
};

class Class_10BB8960
{
public:
    Class_10bb8960_Result* FUN_10bb8960();
};

class Class_10E94578 : public Class_10BC4160
{
public:
    void FUN_10bc5b50();
};

class Class_10E932A0 : public Class_10E94578
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void FUN_10bd2fe0();

    Class_10BB8960* Unknown04;
    char Unknown08[0x38];
    bool Unknown40;
};

// FUNCTION: 0x10BD2FE0 ?FUN_10bd2fe0@Class_10E932A0@@UAEXXZ
void Class_10E932A0::FUN_10bd2fe0()
{
    if ((!FUN_10bc4160()->FUN_10aa82d0() && !Unknown40) || Unknown04->FUN_10bb8960()->Virtual82())
        FUN_10bc5b50();
}

// FUNCTION: 0x10BD3090 ?FUN_10bd3090@Class_10E935F0@@UAEXAAVFArchive@@@Z
void Class_10E935F0::FUN_10bd3090(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    Ar.Serialize(&Unknown44, 4);
    FUN_10b052a0(Ar, Unknown48);
}
