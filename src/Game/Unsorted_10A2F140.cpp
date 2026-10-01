// Game/Unsorted_10A2F140.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6B93C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a2f160(Class_10E6B93C* Other);

    int Unknown04;
};

class Class_10E66300
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10a2f140(int A);

    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10A2F140 ?FUN_10a2f140@Class_10E66300@@UAEHH@Z
int Class_10E66300::FUN_10a2f140(int A)
{
    if (A == Unknown04 || A == Unknown08)
        return 1;
    return 0;
}

// FUNCTION: 0x10A2F160 ?FUN_10a2f160@Class_10E6B93C@@UAEHPAV1@@Z
int Class_10E6B93C::FUN_10a2f160(Class_10E6B93C* Other)
{
    return &Unknown04 == &Other->Unknown04;
}
