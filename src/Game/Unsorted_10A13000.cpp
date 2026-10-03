// Game/Unsorted_10A13000.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A13000_Element
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

class Class_10A13000
{
public:
    bool FUN_10a13000(int A);

    char Unknown00[8];
    int Unknown08;
    char Unknown0C[4];
    Class_10A13000_Element** Unknown10;
};

// FUNCTION: 0x10A13000 ?FUN_10a13000@Class_10A13000@@QAE_NH@Z
bool Class_10A13000::FUN_10a13000(int A)
{
    int Matches = 0;
    for (int i = 0; i < Unknown08; i++)
    {
        if (Unknown10[i]->Virtual20() == A)
            Matches++;
    }
    return Matches > 1;
}
