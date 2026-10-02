// Game/Unsorted_10B3E240_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B3ED20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();

    char Unknown04[0x48];
    bool Unknown4C;
};

class Class_10E7ED00 : public Class_10B3ED20
{
public:
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
    virtual void FUN_10b3e240(int A, int B);

    void FUN_109e38b0(int A, int B);

    char Unknown50[0x20];
    bool Unknown70;
};

class Class_10B39530
{
public:
    void FUN_10b39530(int A, float B, float C, int D, int E, int F, float G);
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10B3E340 : public Class_10AA82D0
{
public:
    void FUN_10b3e340();

    char Unknown04[0x3C];
    int Unknown40;
};

// FUNCTION: 0x10B3E240 ?FUN_10b3e240@Class_10E7ED00@@UAEXHH@Z
void Class_10E7ED00::FUN_10b3e240(int A, int B)
{
    FUN_109e38b0(A, B);
    Unknown70 = true;
}

// FUNCTION: 0x10B3E340 ?FUN_10b3e340@Class_10B3E340@@QAEXXZ
void Class_10B3E340::FUN_10b3e340()
{
    if (Unknown40)
    {
        ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(0xbc, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
        Unknown40 = 0;
    }
}
