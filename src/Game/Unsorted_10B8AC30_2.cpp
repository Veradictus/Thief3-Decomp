// Game/Unsorted_10B8AC30_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B8AC50
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
    virtual Class_10B8AC50* Virtual12();
};

class Class_10E894C8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual Class_10B8AC50* Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual Class_10B8AC50* FUN_10b8ac50();
};

// FUNCTION: 0x10B8AC50 ?FUN_10b8ac50@Class_10E894C8@@UAEPAVClass_10B8AC50@@XZ
Class_10B8AC50* Class_10E894C8::FUN_10b8ac50()
{
    Class_10B8AC50* Target = Virtual7();
    if (Target)
        Target = Target->Virtual12();
    return Target;
}
