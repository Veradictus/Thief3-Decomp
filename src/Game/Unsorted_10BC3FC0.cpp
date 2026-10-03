// Game/Unsorted_10BC3FC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10c00480();

class Class_10BA9EC0
{
public:
    void* FUN_10ba9ec0();
};

class Class_10c00c70
{
public:
    bool FUN_10c00c70();
};

class Class_10BB8300
{
public:
    char Unknown00[8];
    Class_10BA9EC0* Unknown08;
};

class Class_10E8BE68
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual bool FUN_10bc3fc0();
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
    virtual float Virtual65();

    Class_10BB8300* Unknown04;
    char Unknown08[4];
    float Unknown0C;
};

// FUNCTION: 0x10BC3FC0 ?FUN_10bc3fc0@Class_10E8BE68@@UAE_NXZ
bool Class_10E8BE68::FUN_10bc3fc0()
{
    double Limit = Virtual65() + Unknown0C;
    if (FUN_10c00480() < Limit)
        return false;
    if (static_cast<Class_10c00c70*>(Unknown04->Unknown08->FUN_10ba9ec0())->FUN_10c00c70() == 1)
        return false;
    return true;
}
