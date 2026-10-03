// Game/Unsorted_10B48430.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B395B0
{
public:
    void FUN_10b395b0(int A);
};

class Class_10B39700
{
public:
    void FUN_10b39700();
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();

    char Unknown04[4];
    int Unknown08;
    int Unknown0C;
};

class Class_10E7EC40 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual int FUN_10b48510(int A, int B);
};

// FUNCTION: 0x10B48510 ?FUN_10b48510@Class_10E7EC40@@UAEHHH@Z
int Class_10E7EC40::FUN_10b48510(int A, int B)
{
    if (B == 0x41)
    {
        ((Class_10B395B0*)FUN_10aa82d0())->FUN_10b395b0(Unknown08);
        ((Class_10B39700*)FUN_10aa82d0())->FUN_10b39700();
        return 1;
    }
    return Virtual4();
}
