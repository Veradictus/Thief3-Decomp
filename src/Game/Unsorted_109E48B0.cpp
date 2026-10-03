// Game/Unsorted_109E48B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e5b588[];

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    void** Unknown00;
};

class Class_10E5B588 : public Class_10E67FD0
{
public:
    Class_10E5B588* FUN_109e4970();

    char Unknown04[0x120];
    int Unknown124;
};

class Class_10E5B2C0
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
    virtual void Virtual65(int Param);
    virtual void Virtual66(int Param);
    virtual void FUN_109e48b0(int Param);
    virtual void FUN_109e4900(int Param);

    char Unknown04[0xB4];
    int UnknownB8;
    char UnknownBC[4];
    Class_10E5B2C0** UnknownC0;
};

// FUNCTION: 0x109E48B0 ?FUN_109e48b0@Class_10E5B2C0@@UAEXH@Z
void Class_10E5B2C0::FUN_109e48b0(int Param)
{
    for (int i = 0; i < UnknownB8; i++)
    {
        Class_10E5B2C0* Child = UnknownC0[i];
        if (Child)
        {
            Child->Virtual65(Param);
            UnknownC0[i]->FUN_109e48b0(Param);
        }
    }
}

// FUNCTION: 0x109E4900 ?FUN_109e4900@Class_10E5B2C0@@UAEXH@Z
void Class_10E5B2C0::FUN_109e4900(int Param)
{
    for (int i = 0; i < UnknownB8; i++)
    {
        Class_10E5B2C0* Child = UnknownC0[i];
        if (Child)
        {
            Child->Virtual66(Param);
            UnknownC0[i]->FUN_109e4900(Param);
        }
    }
}

// FUNCTION: 0x109E4970 ?FUN_109e4970@Class_10E5B588@@QAEPAV1@XZ
Class_10E5B588* Class_10E5B588::FUN_109e4970()
{
    this->Class_10E67FD0::Class_10E67FD0();
    Unknown00 = DAT_10e5b588;
    Unknown124 = 0;
    return this;
}
