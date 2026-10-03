// Game/Unsorted_10B92CE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Object_10B92CE0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A);

    int Unknown04;
};

class Class_10D9FEE0 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Object_10B92CE0* Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void FUN_10da03a0(int A);
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void FUN_10d9fdb0();
};

class Class_10E894C8 : public Class_10D9FEE0
{
public:
    virtual void FUN_10b92ce0(int A);
    virtual void FUN_10b92d70();
};

// FUNCTION: 0x10B92CE0 ?FUN_10b92ce0@Class_10E894C8@@UAEXH@Z
void Class_10E894C8::FUN_10b92ce0(int A)
{
    Class_10D9FEE0::FUN_10da03a0(A);
    if (Virtual6() && Virtual6()->Unknown04 == 2)
        Virtual6()->Virtual2(A);
}

// FUNCTION: 0x10B92D70 ?FUN_10b92d70@Class_10E894C8@@UAEXXZ
void Class_10E894C8::FUN_10b92d70()
{
    Class_10D9FEE0::FUN_10d9fdb0();
    if (Virtual6() && Virtual6()->Unknown04 == 2)
        Virtual6()->Virtual2(FUN_10aa82d0());
}
