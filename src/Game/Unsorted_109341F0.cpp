// Game/Unsorted_109341F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E49EE0;

class Class_10E49EE0_Owner
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
    virtual void Virtual9(Class_10E49EE0* Object);
};

class Class_10E49EE0
{
public:
    virtual int FUN_109341e0();
    virtual int FUN_109341f0();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual ~Class_10E49EE0();

    Class_10E49EE0_Owner* Unknown04;
    int Unknown08;
};

// FUNCTION: 0x109341F0 ?FUN_109341f0@Class_10E49EE0@@UAEHXZ
int Class_10E49EE0::FUN_109341f0()
{
    int Count = --Unknown08;
    if (Count == 0)
    {
        Unknown04->Virtual9(this);
        delete this;
    }
    return Count;
}
