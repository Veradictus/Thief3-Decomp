// Game/Unsorted_10934890.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E49EE0_Member
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
    virtual int __stdcall Virtual3();
    virtual int __stdcall Virtual4();
    virtual int __stdcall Virtual5();
    virtual int __stdcall Virtual6();
    virtual int __stdcall Virtual7();
    virtual int __stdcall Virtual8();
    virtual int __stdcall Virtual9();
    virtual int __stdcall Virtual10();
    virtual int __stdcall Virtual11();
    virtual int __stdcall Virtual12();
};

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
    virtual int FUN_10934a20();

    char Unknown04[0x10];
    Class_10E49EE0_Member* Unknown14;
};

class Class_10936AC0
{
public:
    void FUN_10936ac0(int A, int B);
};

extern Class_10936AC0* DAT_10f31be0;

class Class_10E49F64
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
    virtual int FUN_10934a40(int A);

    char Unknown04[0x10];
    int Unknown14;
    char Unknown18[4];
    int Unknown1C;
    int Unknown20;
};

class Class_10934DB0_Member
{
public:
    virtual void __stdcall Virtual0();
    virtual void __stdcall Virtual1();
    virtual void __stdcall Virtual2();
};

class Class_10934DB0
{
public:
    void FUN_10934db0();

    Class_10934DB0_Member* Unknown00;
};

// FUNCTION: 0x10934A20 ?FUN_10934a20@Class_10E49EE0@@UAEHXZ
int Class_10E49EE0::FUN_10934a20()
{
    if (Unknown14 == 0)
        return 0x80040721;
    return Unknown14->Virtual12();
}

// FUNCTION: 0x10934A40 ?FUN_10934a40@Class_10E49F64@@UAEHH@Z
int Class_10E49F64::FUN_10934a40(int A)
{
    if (Unknown14 == 0)
        return 0x80040721;
    if (Unknown1C == 0)
        return 0x80040722;
    DAT_10f31be0->FUN_10936ac0(Unknown14, Unknown20);
    return 0;
}

// FUNCTION: 0x10934DB0 ?FUN_10934db0@Class_10934DB0@@QAEXXZ
void Class_10934DB0::FUN_10934db0()
{
    if (Unknown00)
    {
        Unknown00->Virtual2();
        Unknown00 = 0;
    }
}
