// Game/Unsorted_10A62AE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6AC50_Unknown1C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
};

class Class_10E6AC50
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
    virtual void FUN_10a62ae0();

    char Unknown04[0xC];
    int Unknown10;
    int Unknown14;
    char Unknown18[4];
    Class_10E6AC50_Unknown1C** Unknown1C;
};

// FUNCTION: 0x10A62AE0 ?FUN_10a62ae0@Class_10E6AC50@@UAEXXZ
void Class_10E6AC50::FUN_10a62ae0()
{
    Unknown10 = -1;
    for (int i = 0; i < Unknown14; i++)
    {
        Class_10E6AC50_Unknown1C* Item = Unknown1C[i];
        if (Item->Virtual4())
            Item->Virtual9();
    }
}
