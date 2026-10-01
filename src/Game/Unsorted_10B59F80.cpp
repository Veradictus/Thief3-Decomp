// Game/Unsorted_10B59F80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A55050
{
public:
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
    void FUN_10b5a390();

    char Unknown00[0x11C];
    Class_10A55050* Unknown11C;
    char Unknown120[4];
    int Unknown124;
    char Unknown128[8];
    int Unknown130;
    Class_10A64D50 Unknown134;
};

extern void* GWindowManager[];

void* FUN_10b154c0();

class Class_109E8930
{
public:
    void FUN_109e8930(void* Window);
};

class Class_10B15960
{
public:
    bool FUN_10b15960(int A);
};

class Class_10B5A3D0
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

    void FUN_10b5a3d0();
};

// FUNCTION: 0x10B5A390 ?FUN_10b5a390@Class_10B5A390@@QAEXXZ
void Class_10B5A390::FUN_10b5a390()
{
    Unknown124 = 0;
    Unknown134.FUN_10a64d50();
    Unknown130 = 0;
    if (Unknown11C)
        Unknown11C->FUN_10a55050(Unknown130);
}

// FUNCTION: 0x10B5A3D0 ?FUN_10b5a3d0@Class_10B5A3D0@@QAEXXZ
void Class_10B5A3D0::FUN_10b5a3d0()
{
    Virtual56(0);
    static_cast<Class_109E8930*>(GWindowManager[0])->FUN_109e8930(this);
    static_cast<Class_10B15960*>(FUN_10b154c0())->FUN_10b15960(0);
}
