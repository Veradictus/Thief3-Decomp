// Game/Unsorted_10A905F0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C08940
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

class Class_10978090
{
public:
    virtual void Virtual0();

    Class_10C08940* FUN_10978090();

    Class_10C08940* Unknown04;
};

class Class_10AAB5C0 : public Class_10978090
{
public:
    int Unknown08;
};

class Class_10E5B578
{
public:
    virtual void Virtual0() = 0;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6C9E0 : public Class_10AAB5C0, public Class_10E5B578
{
public:
    virtual void Virtual1();
    virtual void FUN_10a90b70();
};

// FUNCTION: 0x10A90B70 ?FUN_10a90b70@Class_10E6C9E0@@UAEXXZ
void Class_10E6C9E0::FUN_10a90b70()
{
    DAT_10f46da0->Virtual1(this, 0x11, FUN_10978090()->Virtual8(), -1);
}
