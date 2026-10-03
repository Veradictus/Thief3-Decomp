// Game/Unsorted_10A53D90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A54CB0 {
public:
    char Unknown00[0x118];
    void* Unknown118;

    bool FUN_10a54cb0();
};

class Class_10AF7F80
{
public:
    const char* FUN_10af7f80();
};

class Class_10950230
{
public:
    void FUN_10950230();
    bool FUN_10dbbbb0();
};

class Config
{
public:
    static Config* Instance();

    bool GetBool(const char* Section, const char* Key, bool* Value, const char* File);
};

class Class_1090A780
{
public:
    Class_1090A780() : Unknown00(0) {}
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Window
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void LoadConfig(Class_10AF7F80* File, Class_10AF7F80* Section);
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

    void FUN_10a53560(int A);

    char Unknown04[0x114];
};

class Class_10E682F0 : public Window
{
public:
    virtual void LoadConfig(Class_10AF7F80* File, Class_10AF7F80* Section);

    void FUN_10a54c70(int A);

    Class_10950230* Unknown118;
    Class_1090A780 Unknown11C;
    char Unknown120;
    bool AlterGamma;
};

// FUNCTION: 0x10A54C20 ?LoadConfig@Class_10E682F0@@UAEXPAVClass_10AF7F80@@0@Z
void Class_10E682F0::LoadConfig(Class_10AF7F80* File, Class_10AF7F80* Section)
{
    Window::LoadConfig(File, Section);
    Config::Instance()->GetBool(Section->FUN_10af7f80(), "AlterGamma", &AlterGamma, File->FUN_10af7f80());
}

// FUNCTION: 0x10A54C70 ?FUN_10a54c70@Class_10E682F0@@QAEXH@Z
void Class_10E682F0::FUN_10a54c70(int A)
{
    FUN_10a53560(A);
    if (Unknown118)
    {
        Unknown118->FUN_10950230();
        if (Unknown118->FUN_10dbbbb0())
            Virtual109();
    }
}

// FUNCTION: 0x10A54CB0 ?FUN_10a54cb0@Class_10A54CB0@@QAE_NXZ
bool Class_10A54CB0::FUN_10a54cb0()
{
    return Unknown118 != 0;
}
