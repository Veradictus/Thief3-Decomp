// Game/Unsorted_10A13150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E5D548_Unknown10
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
    virtual int Virtual20();
};

class Class_10E5D548
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
    virtual Class_10E5D548_Unknown10* FUN_10a13150(int A);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[4];
    Class_10E5D548_Unknown10** Unknown10;
};

// FUNCTION: 0x10A13150 ?FUN_10a13150@Class_10E5D548@@UAEPAVClass_10E5D548_Unknown10@@H@Z
Class_10E5D548_Unknown10* Class_10E5D548::FUN_10a13150(int A)
{
    for (int i = 0; i < Unknown08; i++)
    {
        if (Unknown10[i]->Virtual20() == A)
            return Unknown10[i];
    }
    return 0;
}
