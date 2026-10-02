// Game/Unsorted_10B92CC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B92CC0
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

    int Unknown04;
};

class Class_10E894C8
{
public:
    virtual void Virtual0();
    virtual void FUN_10b92cc0();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Object_10B92CC0* Virtual6();
};

// FUNCTION: 0x10B92CC0 ?FUN_10b92cc0@Class_10E894C8@@UAEXXZ
void Class_10E894C8::FUN_10b92cc0()
{
    Object_10B92CC0* Obj = Virtual6();
    if (Obj && Obj->Unknown04 == 2)
        Obj->Virtual14();
}
