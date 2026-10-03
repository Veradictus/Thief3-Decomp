// Game/Unsorted_10C3D590.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9B168;

float FUN_10c3db60(Class_10E9B168* Obj);

class Class_10c341b0
{
public:
    int FUN_10c341b0();
};

class Class_109BBBA0
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

    void FUN_109b2990(float A, float B, int C, int D, float E, int F, int G);
};

class Class_10E9B168_Unknown30
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
    virtual bool Virtual21();
};

class Class_10E9B168
{
public:
    virtual void Virtual0();
    virtual bool FUN_10c3d590(Class_10E9B168* Other);
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int Virtual5();
    virtual int Virtual6();
    virtual void Virtual7();
    virtual void FUN_10c3ddd0();

    char Unknown04[4];
    Class_10c341b0* Unknown08;
    int Unknown0C;
    int Unknown10;
    char Unknown14[4];
    bool Unknown18;
    char Unknown19[0x17];
    Class_10E9B168_Unknown30 Unknown30;
    char Unknown34[0x20];
    int Unknown54;
    unsigned char Unknown58;
    char Unknown59[7];
    float Unknown60;
    Class_109BBBA0* Unknown64;
    char Unknown68[0x10];
    int Unknown78;
};

// FUNCTION: 0x10C3D590 ?FUN_10c3d590@Class_10E9B168@@UAE_NPAV1@@Z
bool Class_10E9B168::FUN_10c3d590(Class_10E9B168* Other)
{
    if (Unknown30.Virtual21() != true
        && Other->Virtual5() == Unknown0C
        && Other->Virtual6() == Unknown10
        && Other->Unknown78 == Unknown78)
        return !Other->Unknown30.Virtual21();
    return false;
}
