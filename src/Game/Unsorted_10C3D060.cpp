// Game/Unsorted_10C3D060.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

extern float DAT_10f069d8;

struct Struct_10C05A50
{
    float Unknown00;
    float Unknown04;
};

float FUN_10c05a20(const Struct_10C05A50* A, const Struct_10C05A50* B);

struct Struct_10C3D0A0
{
    char Unknown00[0x2C];
    Struct_10C05A50 Unknown2C;
};

class Class_10E9B168
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
    virtual int FUN_10c3d0a0();

    Struct_10C3D0A0* Unknown04;
    char Unknown08[0x14];
    Struct_10C05A50 Unknown1C;
    char Unknown24[4];
    float Unknown28;
};

// FUNCTION: 0x10C3D080 ?FUN_10c3d080@@YAXM@Z
void FUN_10c3d080(float Arg)
{
    if (Arg > DAT_10eafbdc)
        DAT_10f069d8 = Arg;
}

// FUNCTION: 0x10C3D0A0 ?FUN_10c3d0a0@Class_10E9B168@@UAEHXZ
int Class_10E9B168::FUN_10c3d0a0()
{
    if (FUN_10c05a20(&Unknown04->Unknown2C, &Unknown1C) < Unknown28)
        return 1;
    return 0;
}
