// Game/Unsorted_10B7AC90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109B5DB0
{
public:
    float FUN_109b5db0(int A, int B);
};

class Class_10B7AD20
{
public:
    float FUN_10b7ad20(int Index);

    int Unknown00;
    Class_109B5DB0* Unknown04;
    char Unknown08[0xC];
    int Unknown14;
    char Unknown18[0x10];
    int Unknown28;
};

extern float DAT_10eafbdc;

class Class_109B6CD0
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
    virtual void Virtual60(int A);

    void FUN_109b6cd0(int A);
};

class Class_10B7AC90
{
public:
    void FUN_10b7ac90(bool A);

    char Unknown00[4];
    Class_109B6CD0* Unknown04;
    char Unknown08[0xC];
    int Unknown14;
};

// FUNCTION: 0x10B7AC90 ?FUN_10b7ac90@Class_10B7AC90@@QAEX_N@Z
void Class_10B7AC90::FUN_10b7ac90(bool A)
{
    Unknown04->Virtual60(Unknown14);
    Unknown04->FUN_109b6cd0(!A);
}

// FUNCTION: 0x10B7AD20 ?FUN_10b7ad20@Class_10B7AD20@@QAEMH@Z
float Class_10B7AD20::FUN_10b7ad20(int Index)
{
    if (Unknown28 > Index)
        return Unknown04->FUN_109b5db0(Unknown14, Index);
    return DAT_10eafbdc;
}
