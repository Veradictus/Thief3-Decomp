// Game/Unsorted_10951B20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10e4a668
{
public:
    virtual void FUN_10942000(int A);
    virtual void FUN_10942030(int A);
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

    void FUN_10948960(int A);

    char Unknown04[0x58];
    int Unknown5C;
    int Unknown60;
};

class Class_10E4AC78 : public Class_10e4a668
{
public:
    virtual void FUN_10951b20(int A);
};

// FUNCTION: 0x10951B20 ?FUN_10951b20@Class_10E4AC78@@UAEXH@Z
void Class_10E4AC78::FUN_10951b20(int A)
{
    Unknown60 = 0;
    if (!(Unknown5C & 0x11))
    {
        if (Unknown5C & 0x24)
        {
            Virtual23();
            Unknown60 |= 0x100;
        }
    }
    else
    {
        FUN_10948960(0);
        Virtual23();
        Unknown60 |= 0x100;
    }
    Unknown5C = 0;
}
