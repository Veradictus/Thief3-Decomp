// Game/Unsorted_10A3A4E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6678C_UnknownFC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
};

class Class_10E6678C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10a3a630();
    virtual void Virtual6();
    virtual void FUN_10a3a3f0();

    char Unknown04[0xF0];
    int UnknownF4;
    char UnknownF8[4];
    Class_10E6678C_UnknownFC** UnknownFC;
    char Unknown100[0x34];
    char Unknown134;
};

// FUNCTION: 0x10A3A630 ?FUN_10a3a630@Class_10E6678C@@UAEXXZ
void Class_10E6678C::FUN_10a3a630()
{
    for (int i = 0; i < UnknownF4; i++)
        UnknownFC[i]->Virtual4();
}
