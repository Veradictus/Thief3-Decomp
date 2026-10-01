// Game/Unsorted_10B2C050.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B2E000
{
public:
    void FUN_10b2cb50(int p1);
    void FUN_10b2e000(int p1, int p2);

    char Unknown00[0x11C];
    int Unknown11C;
};

class Class_10A51A40
{
public:
    void FUN_10a51a40(int A, int B);
};

class Class_10B2E6F0
{
public:
    void FUN_10b2e6f0();

    char Unknown00[0x118];
    Class_10A51A40* Unknown118;
    Class_10A51A40* Unknown11C;
    char Unknown120[0x29];
    bool Unknown149;
};

class Class_10B2E770_Field124
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
};

class Class_10B2E770
{
public:
    void FUN_10b2e770();

    char Unknown00[0x124];
    Class_10B2E770_Field124* Unknown124;
};

class Struct_10B2E890
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

class Class_10B2E890
{
public:
    void FUN_10b2e890(bool A);

    char Unknown00[0x120];
    Struct_10B2E890* Unknown120;
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

    int Unknown118;
    int Unknown11C;
    int Unknown120;
    int Unknown124;
    int Unknown128;
    int Unknown12C;
    int Unknown130;
    int Unknown134;
    bool Unknown138;
    FArray Unknown13C;
    bool Unknown148;
    bool Unknown149;
};

// FUNCTION: 0x10B2E000 ?FUN_10b2e000@Class_10B2E000@@QAEXHH@Z
void Class_10B2E000::FUN_10b2e000(int p1, int p2)
{
    Unknown11C = p2;
    FUN_10b2cb50(p1);
}

// FUNCTION: 0x10B2E6F0 ?FUN_10b2e6f0@Class_10B2E6F0@@QAEXXZ
void Class_10B2E6F0::FUN_10b2e6f0()
{
    Class_10A51A40* P = Unknown149 ? Unknown11C : Unknown118;
    if (P)
        P->FUN_10a51a40(0, 0);
}

// FUNCTION: 0x10B2E770 ?FUN_10b2e770@Class_10B2E770@@QAEXXZ
void Class_10B2E770::FUN_10b2e770()
{
    if (Unknown124)
        Unknown124->Virtual98();
}

// FUNCTION: 0x10B2E890 ?FUN_10b2e890@Class_10B2E890@@QAEX_N@Z
void Class_10B2E890::FUN_10b2e890(bool A)
{
    if (Unknown120)
    {
        if (A)
            Unknown120->Virtual56(1);
        else
            Unknown120->Virtual56(0);
    }
}

// FUNCTION: 0x10B2E960 ??0Class_10E7B6E8@@QAE@XZ
Class_10E7B6E8::Class_10E7B6E8()
    : Unknown118(0), Unknown11C(0), Unknown120(0), Unknown124(0), Unknown128(0), Unknown12C(0), Unknown130(0),
      Unknown134(0), Unknown138(false), Unknown148(false), Unknown149(false)
{
}

// FUNCTION: 0x10B2EF90 ??_GClass_10E7B6E8@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B2E960's definition in this unit.
