// Game/Unsorted_109427A0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109481F0
{
    char Unknown00[0x28];
    int Unknown28;
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
    virtual void Virtual8();
    virtual void Virtual9(int A, int B);
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void FUN_10942830();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual bool Virtual16();
    virtual bool FUN_109481f0();

    char Unknown04[0xAC];
    Struct_109481F0* Unknown0B0;
    char Unknown0B4[0x3C];
    int Unknown0F0;
};

// FUNCTION: 0x10942830 ?FUN_10942830@Class_10E4A668@@UAEXXZ
void Class_10E4A668::FUN_10942830()
{
    Virtual8();
    for (int i = 0; i < Unknown0F0; i++)
        Virtual9(0, i);
}
