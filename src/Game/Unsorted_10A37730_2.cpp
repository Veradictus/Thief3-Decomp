// Game/Unsorted_10A37730_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A37810
{
public:
    int FUN_10a37810();

    char Unknown00[0x20];
    int Unknown20;
    int Unknown24;
    int Unknown28;
};

struct Struct_10A378B0
{
    char Unknown00[4];
    char Unknown04[0x3C];
    bool Unknown40;
    char Unknown41[0x25F];
    int Unknown2A0;
};

class Class_10924E80
{
public:
    void FUN_10925c60(void* A, int B);
};

extern Class_10924E80* DAT_10f2c734;

class UClient
{
public:
    char Unknown00[0x70];
    int Unknown70;
};

class UEngine
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

    char Unknown04[0x34];
    UClient* Client;
};

extern UEngine* GEngine;

class Class_10A37A30
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, int B, float C);
};

class Class_10E66530
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void FUN_10a37a30(int A, Class_10A37A30* B);
};

struct Info_10A399C0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E666A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10a399c0(const Info_10A399C0* In);

    char Unknown04[0x28];
    Info_10A399C0 Unknown2C;
};

// FUNCTION: 0x10A37810 ?FUN_10a37810@Class_10A37810@@QAEHXZ
int Class_10A37810::FUN_10a37810()
{
    return Unknown20 ? Unknown20 : Unknown28;
}

// FUNCTION: 0x10A378B0 ?FUN_10a378b0@@YGXPAUStruct_10A378B0@@@Z
void __stdcall FUN_10a378b0(Struct_10A378B0* A)
{
    A->Unknown40 = true;
    DAT_10f2c734->FUN_10925c60(A->Unknown04, 0);
    GEngine->Client->Unknown70 = A->Unknown2A0;
    GEngine->Virtual35();
}

// FUNCTION: 0x10A37A30 ?FUN_10a37a30@Class_10E66530@@UAEXHPAVClass_10A37A30@@@Z
void Class_10E66530::FUN_10a37a30(int A, Class_10A37A30* B)
{
    B->Virtual5(-1, 0, -1.0f);
}

// FUNCTION: 0x10A399C0 ?FUN_10a399c0@Class_10E666A0@@UAEXPBUInfo_10A399C0@@@Z
void Class_10E666A0::FUN_10a399c0(const Info_10A399C0* In)
{
    Unknown2C = *In;
}
