// Game/Unsorted_10A6DA80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E67938
{
public:
    virtual void FUN_10a4c470(int Type, int A, int B, int C);
};

class Class_10E6BA00 : public Class_10E67938
{
public:
    virtual void FUN_10a6e6b0(int Type, int A, int B, int C);
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
    virtual void Virtual15(int A, int B, int C);
};

// FUNCTION: 0x10A6E6B0 ?FUN_10a6e6b0@Class_10E6BA00@@UAEXHHHH@Z
void Class_10E6BA00::FUN_10a6e6b0(int Type, int A, int B, int C)
{
    if (Type != 0x26)
        Class_10E67938::FUN_10a4c470(Type, A, B, C);
    else
        Virtual15(A, B, C);
}
