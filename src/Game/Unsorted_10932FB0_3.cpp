// Game/Unsorted_10932FB0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    virtual int FUN_109330c0(unsigned int Index, void* A, void** Out);

    int Unknown04;
    Object_109331D0* Unknown08;
    unsigned int Unknown0C;
    Class_10933230** Unknown10;
};

// FUNCTION: 0x109330C0 ?FUN_109330c0@Class_10E49D44@@UAEHIPAXPAPAX@Z
int Class_10E49D44::FUN_109330c0(unsigned int Index, void* A, void** Out)
{
    if (!Out)
        return 0x80070057;
    *Out = 0;
    if (Index >= Unknown0C)
        return 0x80070057;
    *Out = Unknown10[Index]->Virtual2(A);
    return 0;
}
