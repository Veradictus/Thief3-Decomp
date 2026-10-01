// Game/Unsorted_10AC2610.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6F5F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10ac2610(float Value);
};

class UClient
{
public:
    char Unknown00[0x68];
    float Unknown68;
    float Unknown6C;
    float Unknown70;
};

class UEngine
{
public:
    char Unknown00[0x38];
    UClient* Client;
};

extern UEngine* GEngine;

class Options
{
public:
    void FUN_10ab5c60(int A);
};

Options* FUN_10929550();

class Class_10E6F910
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
    virtual float FUN_10ac2cc0();
};

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

struct Struct_10AA3520
{
    char Unknown00[8];
    Class_1098E330* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10AC2E40
{
public:
    float FUN_10ac2e40();

    char Unknown00[0x604];
    float Unknown604;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E6F61C
{
public:
    virtual void FUN_10ac39b0(int p1, int p2, int p3, int p4);

    char Unknown04[0x554];
    Class_10BFBD70 Unknown558;
};

// FUNCTION: 0x10AC2610 ?FUN_10ac2610@Class_10E6F5F0@@UAEHM@Z
int Class_10E6F5F0::FUN_10ac2610(float Value)
{
    if (Value < 0.33f)
        return 1;
    return 0;
}

// FUNCTION: 0x10AC2CC0 ?FUN_10ac2cc0@Class_10E6F910@@UAEMXZ
float Class_10E6F910::FUN_10ac2cc0()
{
    float Saved70 = GEngine->Client->Unknown70;
    float Saved68 = GEngine->Client->Unknown68;
    float Saved6C = GEngine->Client->Unknown6C;
    FUN_10929550()->FUN_10ab5c60(8);
    float Result = GEngine->Client->Unknown70;
    GEngine->Client->Unknown70 = Saved70;
    GEngine->Client->Unknown68 = Saved68;
    GEngine->Client->Unknown6C = Saved6C;
    return Result;
}

// FUNCTION: 0x10AC2E40 ?FUN_10ac2e40@Class_10AC2E40@@QAEMXZ
float Class_10AC2E40::FUN_10ac2e40()
{
    float Current = Unknown604;
    float Max = 75.0f;
    if (DAT_10f35dec->Unknown08)
        DAT_10f35dec->Unknown08->FUN_1098e330(0x100534, (int*)&Max);
    return Current / Max;
}

// FUNCTION: 0x10AC39B0 ?FUN_10ac39b0@Class_10E6F61C@@UAEXHHHH@Z
void Class_10E6F61C::FUN_10ac39b0(int p1, int p2, int p3, int p4)
{
    if (p1 == 0x5a)
        Unknown558.FUN_10bfbd70(0);
}
