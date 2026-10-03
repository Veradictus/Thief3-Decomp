// Game/Unsorted_10A52A90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager
{
public:
    void FUN_109e8ae0(void* Window);
};

extern WindowManager* GWindowManager;

class Class_10A52B30
{
public:
    void FUN_10a52b30();

    char Unknown00[0xB8];
    int UnknownB8;
    char UnknownBC[4];
    void** UnknownC0;
};

class Class_10E67FD0
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
    virtual bool Virtual54();
    virtual void Virtual55();
    virtual void FUN_10a52a90(int A);
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
    virtual void Virtual88(bool A);

    char Unknown04[0xC4];
    int Unknown0C8;
    char Unknown0CC[0x4C];
};

class Class_10E67FB0
{
public:
    virtual void Virtual0();
    virtual void FUN_10a52af0(float DeltaTime);

    float Unknown04;
    float Unknown08;
    float Unknown0C;
    float Unknown10;
    bool Unknown14;
    float Unknown18;
    float Unknown1C;
};

// FUNCTION: 0x10A52A90 ?FUN_10a52a90@Class_10E67FD0@@UAEXH@Z
void Class_10E67FD0::FUN_10a52a90(int A)
{
    bool Old = Virtual54();
    Unknown0C8 = A;
    if (Virtual54() != Old)
        Virtual88(Virtual54());
}

// FUNCTION: 0x10A52AF0 ?FUN_10a52af0@Class_10E67FB0@@UAEXM@Z
void Class_10E67FB0::FUN_10a52af0(float DeltaTime)
{
    if (Unknown14)
        return;
    Unknown1C += DeltaTime;
    Unknown04 = Unknown08 + Unknown10 * (Unknown1C / Unknown18);
    if (Unknown1C >= Unknown18)
    {
        Unknown04 = Unknown0C;
        Unknown14 = true;
    }
}

// FUNCTION: 0x10A52B30 ?FUN_10a52b30@Class_10A52B30@@QAEXXZ
void Class_10A52B30::FUN_10a52b30()
{
    for (int i = 0; i < UnknownB8; i++)
    {
        if (UnknownC0[i])
            GWindowManager->FUN_109e8ae0(UnknownC0[i]);
    }
    UnknownB8 = 0;
}
