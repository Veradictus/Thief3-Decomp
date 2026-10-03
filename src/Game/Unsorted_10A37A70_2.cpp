// Game/Unsorted_10A37A70_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E666A0;

class Class_10E66530
{
public:
    Class_10E66530(Class_10E666A0* A, int B) : Unknown04(A), Unknown08(B) {}

    virtual int FUN_10a37a10(int A, int B, int C);

    Class_10E666A0* Unknown04;
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
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual Class_10E66530* FUN_10a37c10(int A);
};

struct Struct_10A378B0
{
    char Unknown00[4];
    char Unknown04[0x3C];
    bool Unknown40;
};

class Class_10924E80
{
public:
    void FUN_10925cf0(void* A);
};

extern Class_10924E80* DAT_10f2c734;

class UClient
{
public:
    char Unknown00[0x70];
    float Unknown70;
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

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_109081E0 : public Class_1090A780
{
public:
    Class_109081E0(const char* In);
};

class Class_10A37F30
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
    virtual float Virtual15();

    void FUN_10a37f30(Struct_10A378B0* A);
    Class_109081E0 FUN_10a38f00();

    char Unknown04[0x598];
    int Unknown59C;
    char Unknown5A0[4];
    Class_109081E0* Unknown5A4;
};

// FUNCTION: 0x10A37C10 ?FUN_10a37c10@Class_10E666A0@@UAEPAVClass_10E66530@@H@Z
Class_10E66530* Class_10E666A0::FUN_10a37c10(int A)
{
    return new(0, 0, 0, 0, 0) Class_10E66530(this, A);
}

// FUNCTION: 0x10A37F30 ?FUN_10a37f30@Class_10A37F30@@QAEXPAUStruct_10A378B0@@@Z
void Class_10A37F30::FUN_10a37f30(Struct_10A378B0* A)
{
    A->Unknown40 = false;
    DAT_10f2c734->FUN_10925cf0(A->Unknown04);
    if (!Unknown59C)
    {
        GEngine->Client->Unknown70 = Virtual15();
        GEngine->Virtual35();
    }
}
