// Game/Unsorted_10A62A60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A62A60_Param
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
    virtual int Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13(int A);
};

class Class_10A626F0
{
public:
    void FUN_10a64d70();
    void FUN_10a62a60(Class_10A62A60_Param* Container);
};

// FUNCTION: 0x10A62A60 ?FUN_10a62a60@Class_10A626F0@@QAEXPAVClass_10A62A60_Param@@@Z
void Class_10A626F0::FUN_10a62a60(Class_10A62A60_Param* Container)
{
    while (Container->Virtual10() > 0)
        Container->Virtual13(0);
    FUN_10a64d70();
}
