// Game/Class_10E708F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA3520
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
    virtual int Virtual8();
};

class Class_10ACB8B0
{
public:
    void FUN_10acb8b0(int A, int B);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x110];
    Class_10ACB8B0* Unknown110;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10E708F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10ad09d0(int A, Class_10AA3520* Obj, int C);
};

// FUNCTION: 0x10AD09D0 ?FUN_10ad09d0@Class_10E708F0@@UAEHHPAVClass_10AA3520@@H@Z
int Class_10E708F0::FUN_10ad09d0(int A, Class_10AA3520* Obj, int C)
{
    int Value = Obj->Virtual8();
    DAT_10f3a3d8->Unknown110->FUN_10acb8b0(Value, 0);
    return 1;
}
