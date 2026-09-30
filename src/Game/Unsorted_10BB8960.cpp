// Game/Unsorted_10BB8960.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BB8CC0 {
public:
    char Unknown00[0x334];
    unsigned char Field334;
    unsigned char Field335;
    void FUN_10bb8cc0();
};

void FUN_1096a980();

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

class Class_10BBDB10
{
public:
    int FUN_10bbdb10(int Id);

    int Unknown00;
    Class_1098E330* Unknown04;
};

class Class_10BBDC00
{
public:
    int FUN_10bbdc00(int Id);

    char Unknown00[0xC];
    Class_1098E330* Unknown0C;
};

void FUN_1098e290();

class Class_Field04
{
public:
    void FUN_1098e290();
};

class Class_10BBDC70
{
public:
    void FUN_10bbdc70();

    char Unknown00[0xc];
    Class_Field04* Field0c;
};

class Class_10E70A50
{
public:
    Class_10E70A50();

    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_10E5B578
{
public:
    virtual void FUN_10bbe970() = 0;
};

class Class_10E90B00 : public Class_10E70A50, public Class_10E5B578
{
public:
    Class_10E90B00();

    virtual void FUN_10bbe970();
};

class Class_10E8A3E0;

class Class_10BC1840
{
public:
    int FUN_10bc1840(Class_10E8A3E0* Owner, int A, int B, int C, int D);
};

class Class_10E8A3E0
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
    virtual int FUN_10bbeee0(int A, int B, int C, int D);

    char Unknown04[0xBC];
    Class_10BC1840 UnknownC0;
};

class Class_10BBF5C0
{
public:
    int Field00;

    int FUN_10bbf5c0();
};

class Class_10BBF5D0
{
public:
    int Field00;

    int FUN_10bbf5d0();
};

struct Struct_10BC3F90
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BC3F90
{
public:
    Struct_10BC3F90 FUN_10bc3f90();

    char Unknown00[0x22C];
    Struct_10BC3F90 Unknown22C;
};

class Class_10BC4010 {
public:
    char Unknown00[0x10];
    int Field10;
    void FUN_10bc4010(int param);
};

// FUNCTION: 0x10BB8CC0 ?FUN_10bb8cc0@Class_10BB8CC0@@QAEXXZ
void Class_10BB8CC0::FUN_10bb8cc0()
{
    Field334 = 1;
    Field335 = 0;
}

// FUNCTION: 0x10BBADE0 ?FUN_10bbade0@@YAXXZ
void FUN_10bbade0()
{
    FUN_1096a980();
}

// FUNCTION: 0x10BBDB10 ?FUN_10bbdb10@Class_10BBDB10@@QAEHH@Z
int Class_10BBDB10::FUN_10bbdb10(int Id)
{
    int Value = 0;
    Unknown04->FUN_1098e330(Id, &Value);
    return Value;
}

// FUNCTION: 0x10BBDC00 ?FUN_10bbdc00@Class_10BBDC00@@QAEHH@Z
int Class_10BBDC00::FUN_10bbdc00(int Id)
{
    int Value = 0;
    Unknown0C->FUN_1098e330(Id, &Value);
    return Value;
}

// FUNCTION: 0x10BBDC70 ?FUN_10bbdc70@Class_10BBDC70@@QAEXXZ
void Class_10BBDC70::FUN_10bbdc70()
{
    Field0c->FUN_1098e290();
}

// FUNCTION: 0x10BBE640 ??0Class_10E90B00@@QAE@XZ
Class_10E90B00::Class_10E90B00()
{
}

// FUNCTION: 0x10BBEEE0 ?FUN_10bbeee0@Class_10E8A3E0@@UAEHHHHH@Z
int Class_10E8A3E0::FUN_10bbeee0(int A, int B, int C, int D)
{
    return UnknownC0.FUN_10bc1840(this, A, B, C, D);
}

// FUNCTION: 0x10BBF5C0 ?FUN_10bbf5c0@Class_10BBF5C0@@QAEHXZ
int Class_10BBF5C0::FUN_10bbf5c0()
{
    return Field00 + 0x18;
}

// FUNCTION: 0x10BBF5D0 ?FUN_10bbf5d0@Class_10BBF5D0@@QAEHXZ
int Class_10BBF5D0::FUN_10bbf5d0()
{
    return Field00 + 0x24;
}

// FUNCTION: 0x10BC3F90 ?FUN_10bc3f90@Class_10BC3F90@@QAE?AUStruct_10BC3F90@@XZ
Struct_10BC3F90 Class_10BC3F90::FUN_10bc3f90()
{
    return Unknown22C;
}

// FUNCTION: 0x10BC4010 ?FUN_10bc4010@Class_10BC4010@@QAEXH@Z
void Class_10BC4010::FUN_10bc4010(int param)
{
    Field10 = param;
}

// FUNCTION: 0x10BC4030 ?FUN_10bc4030@@YGDH@Z
char __stdcall FUN_10bc4030(int p1)
{
    return 0;
}
