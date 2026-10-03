// Game/Unsorted_10AD04C0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    virtual int Virtual8(int A);
};

class Class_10978090
{
public:
    virtual void Virtual0();

    Class_10C08940* FUN_10978090();

    int Unknown04;
    int Unknown08;
};

class Class_10E70824_Secondary
{
public:
    virtual void Virtual0();
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E70824_Secondary* A, int B, int C);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E70824 : public Class_10978090, public Class_10E70824_Secondary
{
public:
    virtual void Virtual1();
    virtual void FUN_10ad0680();
};

// FUNCTION: 0x10AD0680 ?FUN_10ad0680@Class_10E70824@@UAEXXZ
void Class_10E70824::FUN_10ad0680()
{
    DAT_10f46da0->Virtual1(this, 0x3B, FUN_10978090()->Virtual8(-1));
}
