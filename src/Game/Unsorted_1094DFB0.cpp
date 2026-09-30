// Game/Unsorted_1094DFB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10919190
{
    int Unknown00;
};

void FUN_10919190(Struct_10919190* P);

class Class_1094E050
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
};

extern int DAT_10f2c720;

class Class_10E4AB88
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
    virtual void FUN_1094e050();

    Struct_10919190 Unknown04;
    char Unknown08[0xE0];
    Class_1094E050* Unknown0E8[1];
};

// FUNCTION: 0x1094E050 ?FUN_1094e050@Class_10E4AB88@@UAEXXZ
void Class_10E4AB88::FUN_1094e050()
{
    FUN_10919190(&Unknown04);
    Unknown0E8[DAT_10f2c720]->Virtual8(0);
}
