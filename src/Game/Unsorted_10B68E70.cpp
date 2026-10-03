// Game/Unsorted_10B68E70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B695F0_Member
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
};

class Class_10B695F0
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
    virtual void Virtual102(Class_10B695F0_Member* A);

    void FUN_10b695f0();

    char Unknown04[0x138];
    Class_10B695F0_Member* Unknown13C;
    char Unknown140[4];
    Class_10B695F0_Member* Unknown144;
    Class_10B695F0_Member* Unknown148;
    char Unknown14C[0x34];
    int Unknown180;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0x2C];
};

class Class_10BFBD70
{
public:
    Class_10BFBD70() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    void FUN_10bfbd70(int NewCount);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E85AD8 : public Class_10E67FD0
{
public:
    Class_10E85AD8();

    virtual ~Class_10E85AD8();

    int Unknown118;
    int Unknown11C;
    int Unknown120;
    int Unknown124;
    int Unknown128;
    int Unknown12C;
    int Unknown130;
    int Unknown134;
    int Unknown138;
    int Unknown13C;
    int Unknown140;
    int Unknown144;
    int Unknown148;
    Class_10BFBD70 Unknown14C;
    int Unknown158;
    int Unknown15C;
    int Unknown160;
    int Unknown164;
    int Unknown168;
    int Unknown16C;
    char Unknown170[0xC];
    int Unknown17C;
    int Unknown180;
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int* Obj);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);

    char* Unknown00;
};

class Class_109081E0 : public Class_1090A780
{
public:
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            int* Obj = (int*)Unknown00 - 1;
            FUN_10905aa0()->Virtual5(Obj);
        }
    }
};

Class_109081E0 FUN_1090a660(const char* Text);

class Class_10B69050
{
public:
    Class_109081E0 FUN_10b69050();
};

// FUNCTION: 0x10B69050 ?FUN_10b69050@Class_10B69050@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10B69050::FUN_10b69050()
{
    Class_109081E0 Local = FUN_1090a660("<string=T_TabScreenMissionCompleteTitle>");
    return Local;
}

// FUNCTION: 0x10B695F0 ?FUN_10b695f0@Class_10B695F0@@QAEXXZ
void Class_10B695F0::FUN_10b695f0()
{
    Unknown180 = 2;
    Unknown148->Virtual56(2);
    Unknown144->Virtual56(2);
    Unknown13C->Virtual56(0);
    Virtual102(Unknown148);
}

// FUNCTION: 0x10B69800 ??0Class_10E85AD8@@QAE@XZ
Class_10E85AD8::Class_10E85AD8()
    : Unknown118(0), Unknown11C(0), Unknown120(0), Unknown124(0), Unknown128(0), Unknown12C(0), Unknown130(0),
      Unknown134(0), Unknown138(0), Unknown13C(0), Unknown140(0), Unknown144(0), Unknown148(0), Unknown158(0),
      Unknown15C(0), Unknown160(0), Unknown164(0), Unknown168(0), Unknown16C(0), Unknown17C(0), Unknown180(0)
{
    Unknown0E8 = 6;
}

// FUNCTION: 0x10B6A380 ??_GClass_10E85AD8@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B69800's definition in this unit.
