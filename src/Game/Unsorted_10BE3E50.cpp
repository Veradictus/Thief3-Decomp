// Game/Unsorted_10BE3E50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFD210
{
public:
    void FUN_10bfd210();
};

class Class_10BE3FF0_Field04
{
public:
    char Unknown00[0x30];
    Class_10BFD210 Unknown30;
};

double FUN_10c00480();

extern float DAT_10e49684;

class Class_10BE3FF0
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
    virtual float Virtual65();

    void FUN_10be3ff0();

    Class_10BE3FF0_Field04* Unknown04;
    char Unknown08[4];
    float Unknown0C;
};

class Class_10E90D70
{
public:
    ~Class_10E90D70();

    virtual void Virtual0();
};

class Class_10E95F40 : public Class_10E90D70
{
public:
    ~Class_10E95F40();
};

void FUN_10c07fe0();

void FUN_10c25610();

// FUNCTION: 0x10BE3F90 ??1Class_10E95F40@@QAE@XZ
Class_10E95F40::~Class_10E95F40()
{
    FUN_10c07fe0();
    FUN_10c25610();
}

// FUNCTION: 0x10BE3FF0 ?FUN_10be3ff0@Class_10BE3FF0@@QAEXXZ
void Class_10BE3FF0::FUN_10be3ff0()
{
    Unknown04->Unknown30.FUN_10bfd210();
    Unknown0C = FUN_10c00480() - (Virtual65() + DAT_10e49684);
}
