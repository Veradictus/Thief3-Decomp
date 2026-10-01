// Game/Unsorted_10B215B0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B228E0
{
public:
    bool FUN_10b228e0();
};

class Class_10B1D1B0
{
public:
    Class_10B228E0* FUN_10b1d1b0();
};

struct Struct_10B215B0_Member
{
    char Unknown00[0x2c4];
    Class_10B1D1B0 Unknown2C4;
};

class AGarrett
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
    virtual void Virtual70();
    virtual void Virtual71();
    virtual void Virtual72();
    virtual void Virtual73();
    virtual void Virtual74();
    virtual void Virtual75();
    virtual void Virtual76();
    virtual void Virtual77();
    virtual void Virtual78();
    virtual void Virtual79();
    virtual void Virtual80();
    virtual void Virtual81();
    virtual void Virtual82();
    virtual void Virtual83();
    virtual void Virtual84();
    virtual void Virtual85();
    virtual void Virtual86();
    virtual void Virtual87();
    virtual void Virtual88();
    virtual void Virtual89();
    virtual void Virtual90();
    virtual void Virtual91();
    virtual void Virtual92();
    virtual void Virtual93();
    virtual void Virtual94();
    virtual void Virtual95();
    virtual void Virtual96();
    virtual void Virtual97();
    virtual void Virtual98();
    virtual void Virtual99();
    virtual void Virtual100();
    virtual void Virtual101();
    virtual void Virtual102();
    virtual void Virtual103();
    virtual void Virtual104();
    virtual void Virtual105();
    virtual void Virtual106();
    virtual void Virtual107();
    virtual void Virtual108();
    virtual void Virtual109();
    virtual void Virtual110();
    virtual void Virtual111();
    virtual void Virtual112();
    virtual void Virtual113();
    virtual void Virtual114();
    virtual void Virtual115();
    virtual void Virtual116();
    virtual void Virtual117();
    virtual void Virtual118();
    virtual void Virtual119();
    virtual void Virtual120();
    virtual void Virtual121();
    virtual void Virtual122();
    virtual bool FUN_10b215b0();

    char Unknown04[0xBC];
    Struct_10B215B0_Member* UnknownC0;
};

struct Struct_10B21820_Data
{
    char Unknown00[0x24];
    float Unknown24;
};

struct Struct_10B21820_Object
{
    char Unknown00[0x3a4];
    Struct_10B21820_Data* Unknown3A4;
};

class Class_10B21820
{
public:
    float FUN_10b21820();
    Struct_10B21820_Object* FUN_10991e10();
};

class Class_10B3ED20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();

    void FUN_10b3ed20();
};

class Class_10B22910
{
public:
    void FUN_10b22910();

    char Unknown00[0x90];
    Class_10B3ED20* Unknown90;
};

class Class_10B22D60
{
public:
    void FUN_10b22c10();
    void FUN_10b229c0(void** A, int B);

    char Unknown00[0x90];
    void* Unknown90;
    void* Unknown94;
};

// FUNCTION: 0x10B215B0 ?FUN_10b215b0@AGarrett@@UAE_NXZ
bool AGarrett::FUN_10b215b0()
{
    return UnknownC0->Unknown2C4.FUN_10b1d1b0()->FUN_10b228e0();
}

// FUNCTION: 0x10B21820 ?FUN_10b21820@Class_10B21820@@QAEMXZ
float Class_10B21820::FUN_10b21820()
{
    return FUN_10991e10()->Unknown3A4->Unknown24;
}

// FUNCTION: 0x10B22910 ?FUN_10b22910@Class_10B22910@@QAEXXZ
void Class_10B22910::FUN_10b22910()
{
    if (Unknown90->Virtual4() == 0xB)
        Unknown90->FUN_10b3ed20();
}

// FUNCTION: 0x10B22C10 ?FUN_10b22c10@Class_10B22D60@@QAEXXZ
void Class_10B22D60::FUN_10b22c10()
{
    FUN_10b229c0(&Unknown90, 0x11);
    FUN_10b229c0(&Unknown94, 0x17);
}
