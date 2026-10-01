// Game/Unsorted_10A141D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A15C30
{
public:
    bool FUN_10a15c30(int* p1);
};

class Class_10E5D688
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
    virtual int FUN_10a16b20(int p1);

    char Unknown04[0x30];
    Class_10A15C30 Unknown34;
};

// FUNCTION: 0x10A16B20 ?FUN_10a16b20@Class_10E5D688@@UAEHH@Z
int Class_10E5D688::FUN_10a16b20(int p1)
{
    int Value = p1;
    return Unknown34.FUN_10a15c30(&Value);
}
