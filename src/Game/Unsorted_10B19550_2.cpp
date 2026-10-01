// Game/Unsorted_10B19550_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AA3520_Member
{
    char Unknown00[0x47c];
    int Unknown47C;
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Struct_10AA3520_Member* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

extern void* GWindowManager[];

class Class_10E79488
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
    virtual bool FUN_10b1bcc0(int param);
};

class Class_10ABDC10
{
public:
    void FUN_10abdc10(int A, int B, int C, int D, int E);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x150];
    Class_10ABDC10* Unknown150;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class AT3PlayerController
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
    virtual void FUN_10b1d290(int A, int B, int C, int D);
};

struct Struct_10B1DAF0_Vec
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Struct_10B1DAF0
{
    char Unknown00[0x2C];
    Struct_10B1DAF0_Vec Unknown2C;
    char Unknown38[0x310];
    int Unknown348;
    char Unknown34C[4];
    Struct_10B1DAF0_Vec Unknown350;
    int Unknown35C;
};

// FUNCTION: 0x10B196A0 ?FUN_10b196a0@@YAHXZ
int FUN_10b196a0()
{
    return DAT_10f35dec->Unknown08->Unknown47C;
}

// FUNCTION: 0x10B1BCC0 ?FUN_10b1bcc0@Class_10E79488@@UAE_NH@Z
bool Class_10E79488::FUN_10b1bcc0(int param)
{
    return GWindowManager[0] != 0;
}

// FUNCTION: 0x10B1D290 ?FUN_10b1d290@AT3PlayerController@@UAEXHHHH@Z
void AT3PlayerController::FUN_10b1d290(int A, int B, int C, int D)
{
    DAT_10f3a3d8->Unknown150->FUN_10abdc10(A, B, C, D, 0);
}

// FUNCTION: 0x10B1DAF0 ?FUN_10b1daf0@@YAXPAUStruct_10B1DAF0@@H@Z
void FUN_10b1daf0(Struct_10B1DAF0* Obj, int Value)
{
    Obj->Unknown350 = Obj->Unknown2C;
    Obj->Unknown35C = Value;
    Obj->Unknown348 = 4;
}
