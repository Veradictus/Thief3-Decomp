// Game/Unsorted_10A858C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A858C0
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
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual int Virtual16();
};

extern int DAT_10f3a1c8;

extern Object_10A858C0** DAT_10f3a1d0;

// FUNCTION: 0x10A858C0 ?FUN_10a858c0@@YA_NH@Z
bool FUN_10a858c0(int A)
{
    for (int i = 0; i < DAT_10f3a1c8; i++)
    {
        if (DAT_10f3a1d0[i]->Virtual16() == A)
            return true;
    }
    return false;
}

// FUNCTION: 0x10A85900 ?FUN_10a85900@@YAXH@Z
void FUN_10a85900(int A)
{
    for (int i = 0; i < DAT_10f3a1c8; i++)
    {
        if (DAT_10f3a1d0[i]->Virtual16() == A)
        {
            DAT_10f3a1d0[i]->Virtual8();
            return;
        }
    }
}
