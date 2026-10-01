// Game/Unsorted_10A89070_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f3a1dc;

extern int DAT_10f3a1e0;

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
    virtual bool FUN_10a8ac20();
};

class Class_10E6C6FC {
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
    virtual bool FUN_10a8c1f0();

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10A8AC20 ?FUN_10a8ac20@Class_10E6C620@@UAE_NXZ
bool Class_10E6C620::FUN_10a8ac20()
{
    return DAT_10f3a1dc >= DAT_10f3a1e0;
}

// FUNCTION: 0x10A8C1F0 ?FUN_10a8c1f0@Class_10E6C6FC@@UAE_NXZ
bool Class_10E6C6FC::FUN_10a8c1f0()
{
    return Unknown08 != -1;
}
