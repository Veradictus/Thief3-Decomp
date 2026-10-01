// Game/Unsorted_10B3D4F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10e7e538
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
    virtual void FUN_10b3e160(int p1);
};

extern void* DAT_10e7ec88[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EC88 : public Class_10B3ACB0
{
public:
    Class_10E7EC88* FUN_10b3d4f0();
};

// FUNCTION: 0x10B3D4F0 ?FUN_10b3d4f0@Class_10E7EC88@@QAEPAV1@XZ
Class_10E7EC88* Class_10E7EC88::FUN_10b3d4f0()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7ec88;
    return this;
}

// FUNCTION: 0x10B3E160 ?FUN_10b3e160@Class_10e7e538@@UAEXH@Z
void Class_10e7e538::FUN_10b3e160(int p1)
{
    Virtual4();
}
