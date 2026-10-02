// Game/Unsorted_109427A0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10919190
{
    float Unknown00[16];
};

void FUN_10919190(Struct_10919190* Matrix);

class Class_10936AC0
{
public:
    void FUN_10936b20(int A, int B);
};

extern Class_10936AC0* DAT_10f31be0;

class Class_10E4A668_Field164
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
    virtual void Virtual8(int A);
    virtual int Virtual9();
};

class Class_10E4A668
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
    virtual void FUN_10942860();

    Struct_10919190 Unknown04;
    char Unknown44[0x120];
    Class_10E4A668_Field164* Unknown164;
    int Unknown168;
};

// FUNCTION: 0x10942860 ?FUN_10942860@Class_10E4A668@@UAEXXZ
void Class_10E4A668::FUN_10942860()
{
    FUN_10919190(&Unknown04);
    Unknown164->Virtual8(0);
    DAT_10f31be0->FUN_10936b20(Unknown168, Unknown164->Virtual9());
}
