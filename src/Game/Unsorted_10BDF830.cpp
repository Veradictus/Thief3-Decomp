// Game/Unsorted_10BDF830.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10BDF870
{
    char Unknown00[0x1C];
    unsigned char Unknown1C;
};

class Class_10E955F0
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
    virtual bool FUN_10bdf870(Info_10BDF870* p1);
};

extern void* DAT_10e954d0[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E95050 : public Class_10E90D70
{
public:
    Class_10E95050(int A, int B);

    int Unknown40;
    int Unknown44;
};

class Class_10E954D0 : public Class_10E95050
{
public:
    Class_10E954D0* FUN_10bdf890(int A, int B, int C);

    int Unknown48;
    float Unknown4C;
    float Unknown50;
};

// FUNCTION: 0x10BDF870 ?FUN_10bdf870@Class_10E955F0@@UAE_NPAUInfo_10BDF870@@@Z
bool Class_10E955F0::FUN_10bdf870(Info_10BDF870* p1)
{
    return p1->Unknown1C == 4;
}

// FUNCTION: 0x10BDF890 ?FUN_10bdf890@Class_10E954D0@@QAEPAV1@HHH@Z
Class_10E954D0* Class_10E954D0::FUN_10bdf890(int A, int B, int C)
{
    this->Class_10E95050::Class_10E95050(A, B);
    Unknown00 = DAT_10e954d0;
    Unknown48 = C;
    Unknown4C = -1.0f;
    Unknown50 = 1.5f;
    return this;
}
