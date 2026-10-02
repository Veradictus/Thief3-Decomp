// Game/Unsorted_10932FB0_6.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_109331D0;

class Class_10933230
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void* Virtual2(void* A);
    virtual void* Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(Object_109331D0* A);
};

class Class_10E49D44
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
    virtual int FUN_10933170();

    int Unknown04;
    Object_109331D0* Unknown08;
    unsigned int Unknown0C;
    Class_10933230** Unknown10;
};

// FUNCTION: 0x10933170 ?FUN_10933170@Class_10E49D44@@UAEHXZ
int Class_10E49D44::FUN_10933170()
{
    for (unsigned int i = 0; i < Unknown0C; i++)
        Unknown10[i]->Virtual8(Unknown08);
    return 0;
}
