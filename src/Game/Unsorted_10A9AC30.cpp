// Game/Unsorted_10A9AC30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10978090
{
public:
    int FUN_10978090();
};

class Class_10AA1AC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual Class_10978090* Virtual4(int A);
};

class Object_10A9AC30
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
    virtual void Virtual8(int A);
    virtual void Virtual9();
};

Object_10A9AC30* FUN_10c56cf0();

class Class_10E6D194
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a9ac30(int A, int B, Class_10AA1AC0* C);
};

// FUNCTION: 0x10A9AC30 ?FUN_10a9ac30@Class_10E6D194@@UAEHHHPAVClass_10AA1AC0@@@Z
int Class_10E6D194::FUN_10a9ac30(int A, int B, Class_10AA1AC0* C)
{
    if (C->Virtual4(0)->FUN_10978090() == 1)
    {
        FUN_10c56cf0()->Virtual9();
        return 1;
    }
    FUN_10c56cf0()->Virtual8(1);
    return 1;
}
