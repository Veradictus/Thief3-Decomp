// Game/Unsorted_10A166D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A160C0
{
public:
    int FUN_10a160c0(int A);
};

class Class_10E5D688
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10a166d0(int A);
    virtual void Virtual4();
    virtual bool Virtual5(int A);

    Class_10A160C0 Unknown04;
};

// FUNCTION: 0x10A166D0 ?FUN_10a166d0@Class_10E5D688@@UAEHH@Z
int Class_10E5D688::FUN_10a166d0(int A)
{
    if (!Virtual5(A))
        return 0;
    return Unknown04.FUN_10a160c0(A);
}
