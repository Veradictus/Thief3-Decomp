// Game/Unsorted_10C2EFD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109BBBA0
{
public:
    int FUN_109b59a0(int A);
    void FUN_109bbba0(int A);
};

class Class_109BC840 : public Class_109BBBA0
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
    virtual void FUN_10c2efd0();

    char Unknown04[4];
    Class_10BAA580* Unknown08;
    char Unknown0C[0x92];
    bool Unknown9E;
};

// FUNCTION: 0x10C2EFD0 ?FUN_10c2efd0@Class_10E9AC80@@UAEXXZ
void Class_10E9AC80::FUN_10c2efd0()
{
    if (Unknown9E)
    {
        if (Unknown08->FUN_10baa580()->FUN_109b59a0(4))
        {
            Unknown08->FUN_10baa580()->FUN_109bbba0(4);
            Unknown9E = false;
        }
    }
}
