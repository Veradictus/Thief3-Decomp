// Game/Unsorted_10B2E790.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10A51A40
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

    void FUN_10a51a40(int A, int B);
};

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0x114];
};

class Class_10E7B6E8 : public Class_10E67FD0
{
public:
    Class_10E7B6E8();

    virtual ~Class_10E7B6E8();

    void FUN_10b2e790();
    void FUN_10b2e7e0(bool A);
    void FUN_10b2e840(bool A);

    Class_10A51A40* Unknown118;
    Class_10A51A40* Unknown11C;
    int Unknown120;
    int Unknown124;
    int Unknown128;
    float Unknown12C;
    float Unknown130;
    float Unknown134;
    bool Unknown138;
    FArray Unknown13C;
    bool Unknown148;
    bool Unknown149;
};

// FUNCTION: 0x10B2E790 ?FUN_10b2e790@Class_10E7B6E8@@QAEXXZ
void Class_10E7B6E8::FUN_10b2e790()
{
    if (Unknown149)
    {
        if (Unknown11C)
        {
            Unknown11C->Virtual98();
            Unknown11C->Virtual20();
        }
    }
    else
    {
        if (Unknown118)
        {
            Unknown118->Virtual98();
            Unknown118->Virtual20();
        }
    }
}

// FUNCTION: 0x10B2E840 ?FUN_10b2e840@Class_10E7B6E8@@QAEX_N@Z
void Class_10E7B6E8::FUN_10b2e840(bool A)
{
    if (Unknown130 > DAT_10eafbdc && Unknown134 > DAT_10eafbdc)
    {
        Unknown138 = A;
        Unknown12C = 0.0f;
    }
    if (!A)
        FUN_10b2e7e0(true);
}
