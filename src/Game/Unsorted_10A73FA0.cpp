// Game/Unsorted_10A73FA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E67938
{
public:
    virtual void FUN_10a4c470(int A, int B, int C, int D);
};

class Class_10E6BB88 : public Class_10E67938
{
public:
    virtual void FUN_10a74470(int A, int B, int C, int D);
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

// FUNCTION: 0x10A74470 ?FUN_10a74470@Class_10E6BB88@@UAEXHHHH@Z
void Class_10E6BB88::FUN_10a74470(int A, int B, int C, int D)
{
    if (A == 0x24)
        Virtual15(B, C, D);
    Class_10E67938::FUN_10a4c470(A, B, C, D);
}
