// Game/Unsorted_10A56C50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A57980
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
    virtual void Virtual121(int A);

    void FUN_10a577f0(int A);
    void FUN_10a589e0(int A);

    char Unknown04[0x1E4];
    int Unknown1E8;
    int Unknown1EC;
    int Unknown1F0;
    int Unknown1F4;
};

extern void* DAT_10e68d80;

extern void* DAT_10e7edb8[];

class Class_10E69080
{
public:
    Class_10E69080();

    void** Unknown00;
    char Unknown04[0x114];
    void** Unknown118;
    char Unknown11C[0xB4];
};

class Class_10E68D80 : public Class_10E69080
{
public:
    Class_10E68D80();

    int Unknown1D0;
    int Unknown1D4;
    int Unknown1D8;
    char Unknown1DC;
    int Unknown1E0;
    int Unknown1E4;
    int Unknown1E8;
    int Unknown1EC;
    int Unknown1F0;
    int Unknown1F4;
};

typedef float FLOAT;

class FVector
{
public:
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator+(const FVector& V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }

    FLOAT X, Y, Z;
};

class Class_10E68B10
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual FVector Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual FVector FUN_10a56c50();

    char Unknown04[0x30];
    FLOAT Unknown34;
    FLOAT Unknown38;
    char Unknown3C[0x100];
    FLOAT Unknown13C;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E6AEA0
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
    virtual void FUN_10a572c0(Class_10BFBD70* Array, int B);

    char Unknown04[0x114];
    int Unknown118;
};

// FUNCTION: 0x10A56C50 ?FUN_10a56c50@Class_10E68B10@@UAE?AVFVector@@XZ
FVector Class_10E68B10::FUN_10a56c50()
{
    FVector Ext(Unknown13C, Unknown13C, 0.0f);
    return Ext + Virtual6();
}

// FUNCTION: 0x10A572C0 ?FUN_10a572c0@Class_10E6AEA0@@UAEXPAVClass_10BFBD70@@H@Z
void Class_10E6AEA0::FUN_10a572c0(Class_10BFBD70* Array, int B)
{
    if (Array && Unknown118)
    {
        int Index = Array->Unknown00;
        Array->FUN_10bfbd70(Index + 1);
        Array->Unknown08[Index] = Unknown118;
    }
}

// FUNCTION: 0x10A57790 ??0Class_10E68D80@@QAE@XZ
Class_10E68D80::Class_10E68D80()
{
    Unknown1D0 = 0;
    Unknown1D4 = 0;
    Unknown1D8 = 0;
    Unknown1DC = 0;
    Unknown1E0 = 0;
    Unknown1E4 = 0;
    Unknown1E8 = 0;
    Unknown1EC = 0;
    Unknown1F0 = 0;
    Unknown1F4 = 0;
    Unknown00 = &DAT_10e68d80;
    Unknown118 = DAT_10e7edb8;
}

// FUNCTION: 0x10A577F0 ?FUN_10a577f0@Class_10A57980@@QAEXH@Z
void Class_10A57980::FUN_10a577f0(int A)
{
    FUN_10a589e0(A);
    Virtual121(Unknown1F0);
    Unknown1F4 = Unknown1F0;
}
