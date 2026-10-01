// Game/Unsorted_10A8D350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

extern Class_1090A780 DAT_10f3a1f8[];

class Class_10E6C7B4
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
    virtual Class_1090A780 FUN_10a8d570();

    char Unknown04[0x4];
    int Unknown08;
};

// FUNCTION: 0x10A8D570 ?FUN_10a8d570@Class_10E6C7B4@@UAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10E6C7B4::FUN_10a8d570()
{
    return Class_1090A780(DAT_10f3a1f8[Unknown08]);
}
