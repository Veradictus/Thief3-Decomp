// Game/Unsorted_10B28020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager
{
public:
    void FUN_109e8930(void* Window);
    void FUN_10b158b0();

    char Unknown00[0x264];
    char Unknown264;
};

extern WindowManager* GWindowManager;

void* FUN_10b154c0();

class Class_10B28390
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
    virtual void Virtual56(int A);

    void FUN_10b28390();
};

class Class_10A52A40_Member;

class Class_10A52A40
{
public:
    void FUN_10a52a40(Class_10A52A40_Member* A);
};

class Class_10B282E0_Unknown170
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
    virtual void Virtual56(int A);
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
    virtual void Virtual102(Class_10A52A40_Member* A);
};

class Class_10B282E0 : public Class_10A52A40
{
public:
    void FUN_10b282e0(Class_10A52A40_Member* A);

    char Unknown00[0xC4];
    int Unknown0C4;
    char Unknown0C8[0xA8];
    Class_10B282E0_Unknown170* Unknown170;
};

// FUNCTION: 0x10B282E0 ?FUN_10b282e0@Class_10B282E0@@QAEXPAVClass_10A52A40_Member@@@Z
void Class_10B282E0::FUN_10b282e0(Class_10A52A40_Member* A)
{
    FUN_10a52a40(A);
    if (Unknown170)
    {
        if (Unknown0C4)
            Unknown170->Virtual102(A);
        else
            Unknown170->Virtual56(0);
    }
}

// FUNCTION: 0x10B28390 ?FUN_10b28390@Class_10B28390@@QAEXXZ
void Class_10B28390::FUN_10b28390()
{
    Virtual56(0);
    GWindowManager->FUN_109e8930(this);
    ((WindowManager*)FUN_10b154c0())->Unknown264 = 0;
    ((WindowManager*)FUN_10b154c0())->FUN_10b158b0();
}
