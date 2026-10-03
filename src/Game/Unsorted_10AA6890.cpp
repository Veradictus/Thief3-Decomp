// Game/Unsorted_10AA6890.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    int* Data;
};

class Class_10E6D8F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10aa69a0(int A);
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual int FUN_10aa65c0(int A);
    virtual int Virtual13(int A, int B);

    int Unknown04;
    Class_10BFBD70 Unknown08;
};

// FUNCTION: 0x10AA69A0 ?FUN_10aa69a0@Class_10E6D8F0@@UAEXH@Z
void Class_10E6D8F0::FUN_10aa69a0(int A)
{
    int Old = Unknown08.Count;
    Unknown04 = A;
    Unknown08.FUN_10bfbd70(A);
    for (int i = Old; i < A; i++)
        Unknown08.Data[i] = 0;
}
