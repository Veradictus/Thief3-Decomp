// Game/Unsorted_10B5A400.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A54FE0
{
public:
    void FUN_10a54fe0(int A);
};

class Class_10A55000
{
public:
    int FUN_10a55000();
};

class Class_10A55050
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
    virtual void Virtual16(int A);
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

    void FUN_10a55050(unsigned char A);
};

class Class_10A64D50
{
public:
    void FUN_10a64d50();
};

class Class_10B5A390
{
public:
    void FUN_10b5a570();

    char Unknown00[0x11C];
    Class_10A55050* Unknown11C;
    char Unknown120[4];
    int Unknown124;
    int Unknown128;
    int Unknown12C;
    int Unknown130;
    Class_10A64D50 Unknown134;
};

// FUNCTION: 0x10B5A570 ?FUN_10b5a570@Class_10B5A390@@QAEXXZ
void Class_10B5A390::FUN_10b5a570()
{
    if (Unknown11C)
    {
        Unknown11C->Virtual36();
        Unknown128 = ((Class_10A55000*)Unknown11C)->FUN_10a55000();
        if (!Unknown128)
            Unknown128 = 1;
        Unknown124 = 0;
        Unknown134.FUN_10a64d50();
        Unknown130 = 0;
        if (Unknown11C)
            Unknown11C->FUN_10a55050(Unknown130);
        Unknown12C = 0;
        Unknown11C->FUN_10a55050(Unknown130);
        ((Class_10A54FE0*)Unknown11C)->FUN_10a54fe0(Unknown12C);
    }
}
