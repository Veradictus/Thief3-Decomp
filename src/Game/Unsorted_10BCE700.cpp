// Game/Unsorted_10BCE700.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void __stdcall FUN_109e3c90(int p1);

class Class_10E92D60
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
    virtual void FUN_10bce8b0();
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
};

class FVector
{
public:
    float X;
    float Y;
    float Z;
};

class AActor
{
public:
    char Unknown00[0x2C];
    FVector Location;
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10E91CB8_Unknown04
{
    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

class Class_10AA6080
{
public:
    bool FUN_10aa6080(FVector* Position, float Distance);
};

int FUN_10aa6040();

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

class Class_10E94578 : public Class_10BC4160
{
public:
    void FUN_10bc5b50();
};

class Class_10E91CB8 : public Class_10E94578
{
public:
    virtual void Virtual1();
    virtual void FUN_10bce760();

    void FUN_10bce210();

    Struct_10E91CB8_Unknown04* Unknown04;
};

// FUNCTION: 0x10BCE760 ?FUN_10bce760@Class_10E91CB8@@UAEXXZ
void Class_10E91CB8::FUN_10bce760()
{
    if (!FUN_10bc4160()->FUN_10aa82d0())
    {
        if (!((Class_10AA6080*)FUN_10aa6040())->FUN_10aa6080(&((AActor*)Unknown04->Unknown08->FUN_10c7d570())->Location, 80.0f))
            FUN_10bc5b50();
        else
            FUN_10bce210();
    }
}

// FUNCTION: 0x10BCE8B0 ?FUN_10bce8b0@Class_10E92D60@@UAEXXZ
void Class_10E92D60::FUN_10bce8b0()
{
    FUN_109e3c90(0);
    Virtual71();
}
