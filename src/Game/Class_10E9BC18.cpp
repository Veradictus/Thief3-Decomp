// Game/Class_10E9BC18.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9bb5c[];

struct Info_10C47FC0
{
    void* Unknown00;
    int Unknown04;
};

class Class_10E9BBC0
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
    virtual void Virtual8(Info_10C47FC0* Info);
};

class Class_10E9BC18
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
    virtual void FUN_10c47fc0(int Value);

    char Unknown04[0xC];
    Class_10E9BBC0 Unknown10;
};

// FUNCTION: 0x10C47FC0 ?FUN_10c47fc0@Class_10E9BC18@@UAEXH@Z
void Class_10E9BC18::FUN_10c47fc0(int Value)
{
    Info_10C47FC0 Info;
    Info.Unknown04 = Value;
    Info.Unknown00 = DAT_10e9bb5c;
    Class_10E9BBC0* Target = &Unknown10;
    Target->Virtual8(&Info);
}
