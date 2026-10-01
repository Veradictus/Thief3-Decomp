// Game/Unsorted_10A8A570_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C5D0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10a8a570();

    Class_10E6C5D0* Unknown04;
};

class Class_10E6C620
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a8abe0(int p1, Class_10E6C620* p2);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10A8A570 ?FUN_10a8a570@Class_10E6C5D0@@UAEHXZ
int Class_10E6C5D0::FUN_10a8a570()
{
    if (!Unknown04)
        return 1;
    return Unknown04->FUN_10a8a570();
}

// FUNCTION: 0x10A8ABE0 ?FUN_10a8abe0@Class_10E6C620@@UAEHHPAV1@@Z
int Class_10E6C620::FUN_10a8abe0(int p1, Class_10E6C620* p2)
{
    switch (p1)
    {
    case 1:
    {
        bool Same = Unknown08 == p2->Unknown08;
        return Same;
    }
    default:
        return 0;
    }
}
