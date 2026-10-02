// Game/Unsorted_10A8AC40_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A8AC40
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual bool Virtual7(Object_10A8AC40** Ref);
};

class Class_10E6C620
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
    virtual int FUN_10a8ac40();

    Object_10A8AC40* Unknown04;
};

// FUNCTION: 0x10A8AC40 ?FUN_10a8ac40@Class_10E6C620@@UAEHXZ
int Class_10E6C620::FUN_10a8ac40()
{
    int Result = Unknown04 && Unknown04->Virtual7(&Unknown04);
    return (unsigned char)Result;
}
