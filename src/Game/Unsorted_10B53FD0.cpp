// Game/Unsorted_10B53FD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B54050_Element
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
    virtual void Virtual70(int A);
};

class Class_10B54050
{
public:
    void FUN_10b54050();

    int Unknown00;
    char Unknown04[0xC];
    Class_10B54050_Element** Unknown10;
};

class FVector
{
public:
    float X;
    float Y;
    float Z;
};

class Class_10B54760_Unknown18
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(FVector* A);
    virtual void Virtual6();
    virtual void Virtual7();
    virtual FVector* Virtual8();
};

class Class_10B54760
{
public:
    void FUN_10b53fd0();

    int Unknown00;
    char Unknown04[0x14];
    Class_10B54760_Unknown18* Unknown18;
};

// FUNCTION: 0x10B53FD0 ?FUN_10b53fd0@Class_10B54760@@QAEXXZ
void Class_10B54760::FUN_10b53fd0()
{
    FVector Location = *Unknown18->Virtual8();
    Location.X = Location.X + 10.0f - Unknown00 * 6;
    Unknown18->Virtual5(&Location);
}

// FUNCTION: 0x10B54050 ?FUN_10b54050@Class_10B54050@@QAEXXZ
void Class_10B54050::FUN_10b54050()
{
    Unknown10[Unknown00]->Virtual70(2);
}
