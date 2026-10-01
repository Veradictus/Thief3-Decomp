// Game/Unsorted_10C12A00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    bool IsEmpty() const
    {
        int Length = Unknown00 == 0 ? 0 : ((int*)Unknown00)[-1];
        return Length == 0;
    }

    char* Unknown00;
};

extern Class_1090A780 DAT_10ff7060;

class Class_10E984BC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10c12a70();
};

// FUNCTION: 0x10C12A70 ?FUN_10c12a70@Class_10E984BC@@UAEHXZ
int Class_10E984BC::FUN_10c12a70()
{
    return DAT_10ff7060.IsEmpty();
}
