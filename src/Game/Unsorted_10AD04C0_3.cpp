// Game/Unsorted_10AD04C0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E70844 : public Class_10AAB5C0, public Class_10E5B578
{
public:
    virtual void Virtual1();
    virtual void FUN_10ad0760();
};

class Class_10E70860 : public Class_10AAB5C0, public Class_10E5B578
{
public:
    virtual void Virtual1();
    virtual void FUN_10ad0840();
};

// FUNCTION: 0x10AD0760 ?FUN_10ad0760@Class_10E70844@@UAEXXZ
void Class_10E70844::FUN_10ad0760()
{
    DAT_10f46da0->Virtual1(this, 6, FUN_10978090()->Virtual8(), -1);
}

// FUNCTION: 0x10AD0840 ?FUN_10ad0840@Class_10E70860@@UAEXXZ
void Class_10E70860::FUN_10ad0840()
{
    DAT_10f46da0->Virtual1(this, 0xF, FUN_10978090()->Virtual8(), -1);
}
