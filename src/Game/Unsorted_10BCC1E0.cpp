// Game/Unsorted_10BCC1E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BB8400
{
public:
    bool FUN_10bb8400();
};

class Class_Field04 : public Class_10BB8400
{
public:
    void FUN_10bb83e0();
};

class Class_10E8BE68
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
    virtual void FUN_10bcc220();

    Class_Field04* Unknown04;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

class Class_10E94578
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
    virtual void FUN_10bcac50(int A, int B, int C, int D, int E);

    void FUN_10bc5b50();
    void FUN_10bcb850(FArchive& Ar);
};

class Class_10E92578 : public Class_10E94578
{
public:
    virtual void FUN_10bcc1e0(int A, int B, int C, int D, int E);
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
    virtual void FUN_10bcc1a0(FArchive& Ar);

    char Unknown04[0x58];
    bool Unknown5C;
    bool Unknown5D;
};

// FUNCTION: 0x10BCC1E0 ?FUN_10bcc1e0@Class_10E92578@@UAEXHHHHH@Z
void Class_10E92578::FUN_10bcc1e0(int A, int B, int C, int D, int E)
{
    Class_10E94578::FUN_10bcac50(A, B, C, D, E);
    if (D != 0x17)
    {
        Unknown5C = true;
        FUN_10bc5b50();
    }
}

// FUNCTION: 0x10BCC220 ?FUN_10bcc220@Class_10E8BE68@@UAEXXZ
void Class_10E8BE68::FUN_10bcc220()
{
    if (Unknown04->FUN_10bb8400())
        Unknown04->FUN_10bb83e0();
}
