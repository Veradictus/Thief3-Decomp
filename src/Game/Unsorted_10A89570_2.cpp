// Game/Unsorted_10A89570_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C5D0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10a8a550();

    Class_10E6C5D0* Unknown04;
};

extern int DAT_10f3a1dc;

extern int DAT_10f3a1e0;

class Class_10E6C620
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10a8ac00();
};

// FUNCTION: 0x10A8A550 ?FUN_10a8a550@Class_10E6C5D0@@UAEXXZ
void Class_10E6C5D0::FUN_10a8a550()
{
    if (Unknown04)
        Unknown04->FUN_10a8a550();
}

// FUNCTION: 0x10A8AC00 ?FUN_10a8ac00@Class_10E6C620@@UAEXXZ
void Class_10E6C620::FUN_10a8ac00()
{
    if (DAT_10f3a1dc < DAT_10f3a1e0)
        DAT_10f3a1dc++;
}
