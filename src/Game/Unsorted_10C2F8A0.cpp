// Game/Unsorted_10C2F8A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct S_10C2F8A0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E9AC80
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
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual bool FUN_10c2f8a0(S_10C2F8A0* Out);

    char Unknown04[0x70];
    S_10C2F8A0 Unknown74;
    char Unknown80[0x1F];
    bool Unknown9F;
};

// FUNCTION: 0x10C2F8A0 ?FUN_10c2f8a0@Class_10E9AC80@@UAE_NPAUS_10C2F8A0@@@Z
bool Class_10E9AC80::FUN_10c2f8a0(S_10C2F8A0* Out)
{
    if (Unknown9F)
    {
        *Out = Unknown74;
        return true;
    }
    return false;
}
