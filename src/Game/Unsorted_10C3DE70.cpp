// Game/Unsorted_10C3DE70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C341B0
{
public:
    int FUN_10c341b0();
};

class Class_109B2990
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
    virtual void Virtual60(int A);

    void FUN_109b2990(int A, float B, int C, int D, float E, int F, int G);
};

class Class_10E9B370;

float FUN_10c3dbc0(Class_10E9B370* Obj);

class Class_10E9B370
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
    virtual void FUN_10c3de70();

    char Unknown04[4];
    Class_10C341B0* Unknown08;
    char Unknown0C[0xC];
    bool Unknown18;
    char Unknown19[0x27];
    int Unknown40;
    unsigned char Unknown44;
    char Unknown45[7];
    int Unknown4C;
    Class_109B2990* Unknown50;
};

// FUNCTION: 0x10C3DE70 ?FUN_10c3de70@Class_10E9B370@@UAEXXZ
void Class_10E9B370::FUN_10c3de70()
{
    Unknown40 = Unknown08->FUN_10c341b0();
    if (Unknown40 != -1)
    {
        Unknown50->Virtual60(Unknown40);
        Unknown50->FUN_109b2990(Unknown4C, FUN_10c3dbc0(this), 0, Unknown44, -1.0f, -1, 0);
        Unknown18 = true;
    }
}
