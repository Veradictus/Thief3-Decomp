// Game/Unsorted_10BD85B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BBDB40
{
public:
    float FUN_10bbdc80();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

struct Struct_10BD8630
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BD8630
{
public:
    float FUN_10bd8630();

    char Unknown00[4];
    Struct_10BD8630* Unknown04;
};

class Class_10BD8650
{
public:
    float FUN_10bd8650();

    char Unknown00[4];
    Struct_10BD8630* Unknown04;
};

void __stdcall FUN_109e3c90(int A);

class Class_10E93F68
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
    virtual void FUN_10bd9640(int A);

    char Unknown04[0x44];
    int Unknown48;
    int Unknown4C;
};

// FUNCTION: 0x10BD8630 ?FUN_10bd8630@Class_10BD8630@@QAEMXZ
float Class_10BD8630::FUN_10bd8630()
{
    float Value = Unknown04->Unknown08->FUN_10dbd510(0x10056c)->FUN_10bbdc80();
    return Value;
}

// FUNCTION: 0x10BD8650 ?FUN_10bd8650@Class_10BD8650@@QAEMXZ
float Class_10BD8650::FUN_10bd8650()
{
    float Value = Unknown04->Unknown08->FUN_10dbd510(0x10056d)->FUN_10bbdc80();
    return Value;
}

// FUNCTION: 0x10BD9640 ?FUN_10bd9640@Class_10E93F68@@UAEXH@Z
void Class_10E93F68::FUN_10bd9640(int A)
{
    FUN_109e3c90(A);
    if (Unknown48 == A)
        Unknown48 = 0;
    if (Unknown4C == A)
        Unknown4C = 0;
}
