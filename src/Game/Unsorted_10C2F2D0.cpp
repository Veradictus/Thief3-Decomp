// Game/Unsorted_10C2F2D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109B2900
{
public:
    void FUN_109b2900();
};

class Class_109BC840 : public Class_109B2900
{
};

class Class_10BAA580
{
public:
    Class_109BC840* FUN_10baa580();
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
    virtual void FUN_10c2f300();

    char Unknown04[4];
    Class_10BAA580* Unknown08;
    char Unknown0C[0xCD];
    bool Unknown0D9;
};

// FUNCTION: 0x10C2F300 ?FUN_10c2f300@Class_10E9AC80@@UAEXXZ
void Class_10E9AC80::FUN_10c2f300()
{
    if (!Unknown0D9 && Unknown08->FUN_10baa580())
        Unknown08->FUN_10baa580()->FUN_109b2900();
}
