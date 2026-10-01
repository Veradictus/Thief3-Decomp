// Game/Unsorted_10A55000.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A242D0
{
public:
    int FUN_10a242d0();
};

class Class_10A55000
{
public:
    int FUN_10a55000();

    char Unknown00[0x12C];
    Class_10A242D0* Unknown12C;
};

class Class_10A52BE0
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
    virtual void FUN_10a52be0(bool Param);
};

class Class_10E684A8 : public Class_10A52BE0
{
public:
    virtual void FUN_10a55020(bool Param);
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
    virtual bool Virtual54();

    char Unknown04[0x11C];
    bool Unknown120;
};

class Class_10A24370
{
public:
    void FUN_10a24370(int p1);

    char Unknown00[0x70];
    char Unknown70;
};

class Class_10A55050
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
    virtual void Virtual16(int A);

    void FUN_10a55050(int A);

    char Unknown04[0x128];
    Class_10A24370* Unknown12c;
};

// FUNCTION: 0x10A55000 ?FUN_10a55000@Class_10A55000@@QAEHXZ
int Class_10A55000::FUN_10a55000()
{
    if (!Unknown12C)
        return 0;
    return Unknown12C->FUN_10a242d0();
}

// FUNCTION: 0x10A55020 ?FUN_10a55020@Class_10E684A8@@UAEX_N@Z
void Class_10E684A8::FUN_10a55020(bool Param)
{
    if (Virtual54())
        Unknown120 = true;
    Class_10A52BE0::FUN_10a52be0(Param);
}

// FUNCTION: 0x10A55050 ?FUN_10a55050@Class_10A55050@@QAEXH@Z
void Class_10A55050::FUN_10a55050(int A)
{
    if ((char)A != Unknown12c->Unknown70)
    {
        Unknown12c->FUN_10a24370(A);
        Virtual16(0);
    }
}
