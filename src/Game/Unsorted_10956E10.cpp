// Game/Unsorted_10956E10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10956E10
{
    int Unknown00;
    char Unknown04[0x34];
};

class Class_10E4AE8C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int FUN_10956e10(int A);
    virtual void Virtual5();
    virtual void Virtual6();
    virtual bool Virtual7(int A);
    virtual void Virtual8();
    virtual void Virtual9();
    virtual bool Virtual10();

    char Unknown04[0xA4];
    Struct_10956E10 Unknown0A8[8];
    char Unknown268[0x34];
    int Unknown29C[8];
};

// FUNCTION: 0x10956E10 ?FUN_10956e10@Class_10E4AE8C@@UAEHH@Z
int Class_10E4AE8C::FUN_10956e10(int A)
{
    if (Virtual10())
        return Unknown29C[A];
    if (Virtual7(A))
        return Unknown0A8[A].Unknown00;
    return 0;
}
