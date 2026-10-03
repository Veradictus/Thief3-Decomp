// Game/Unsorted_10AA6D90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1091CD10
{
public:
    void FUN_1091cd10();
};

class Class_10A52BE0
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
    virtual void FUN_10a52be0(bool Param);
};

class Class_10E822B0 : public Class_10A52BE0
{
public:
    virtual void FUN_10aa7100(bool A);
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

    void FUN_10aa6d90(bool A);

    char Unknown04[0x11C];
    Class_1091CD10* Unknown120;
};

void FUN_10d3d990(void* Stream, int* Value);

class Class_10E6C128
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10aa7150(void* Stream, int A, int B);

    char Unknown04[0xC];
    int Unknown10;
    char Unknown14[8];
    int Unknown1C;
    int Unknown20;
    int Unknown24;
};

// FUNCTION: 0x10AA6D90 ?FUN_10aa6d90@Class_10E822B0@@QAEX_N@Z
void Class_10E822B0::FUN_10aa6d90(bool A)
{
    if (A)
    {
        Class_1091CD10* Object = Unknown120;
        if (Object)
        {
            Object->FUN_1091cd10();
            ::operator delete(Object);
            Unknown120 = 0;
            Virtual109();
        }
    }
}

// FUNCTION: 0x10AA7100 ?FUN_10aa7100@Class_10E822B0@@UAEX_N@Z
void Class_10E822B0::FUN_10aa7100(bool A)
{
    Class_1091CD10* Object = Unknown120;
    if (Object)
    {
        Object->FUN_1091cd10();
        ::operator delete(Object);
        Unknown120 = 0;
        Virtual109();
    }
    Class_10A52BE0::FUN_10a52be0(A);
}

// FUNCTION: 0x10AA7150 ?FUN_10aa7150@Class_10E6C128@@UAEXPAXHH@Z
void Class_10E6C128::FUN_10aa7150(void* Stream, int A, int B)
{
    FUN_10d3d990(Stream, &Unknown24);
    FUN_10d3d990(Stream, &Unknown20);
    FUN_10d3d990(Stream, &Unknown10);
    FUN_10d3d990(Stream, &Unknown1C);
}
