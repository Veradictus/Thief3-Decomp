// Game/Unsorted_10934270.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10936AC0
{
public:
    void FUN_10936ac0(int A, int B);
};

extern Class_10936AC0* DAT_10f31be0;

class Class_10E49EE0
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
    virtual int FUN_109342f0(int A);

    char Unknown04[0x10];
    int Unknown14;
    char Unknown18[8];
    int Unknown20;
};

// FUNCTION: 0x109342F0 ?FUN_109342f0@Class_10E49EE0@@UAEHH@Z
int Class_10E49EE0::FUN_109342f0(int A)
{
    if (Unknown14 == 0)
        return 0x80040721;
    DAT_10f31be0->FUN_10936ac0(Unknown14, Unknown20);
    return 0;
}
