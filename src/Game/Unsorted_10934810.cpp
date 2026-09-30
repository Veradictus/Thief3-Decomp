// Game/Unsorted_10934810.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10936AC0
{
public:
    void FUN_10936ac0(int A, int B);
};

extern Class_10936AC0* DAT_10f31be0;

class Class_10E49F38
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
    virtual int FUN_10934860(int A);

    char Unknown04[0x10];
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

// FUNCTION: 0x10934860 ?FUN_10934860@Class_10E49F38@@UAEHH@Z
int Class_10E49F38::FUN_10934860(int A)
{
    if (Unknown14 == 0)
        return 0x80040721;
    DAT_10f31be0->FUN_10936ac0(Unknown14, Unknown1C);
    return 0;
}
