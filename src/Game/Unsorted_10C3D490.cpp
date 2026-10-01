// Game/Unsorted_10C3D490.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_109B6520
{
public:
    float FUN_109b6520(int A);
};

class Class_10E9B0F8
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
    virtual float FUN_10c3d490();

    char Unknown04[0x20];
    int Unknown24;
    char Unknown28[0xC];
    Class_109B6520* Unknown34;
};

// FUNCTION: 0x10C3D490 ?FUN_10c3d490@Class_10E9B0F8@@UAEMXZ
float Class_10E9B0F8::FUN_10c3d490()
{
    if (Unknown24 >= 0)
        return Unknown34->FUN_109b6520(Unknown24);
    return DAT_10eafbdc;
}
