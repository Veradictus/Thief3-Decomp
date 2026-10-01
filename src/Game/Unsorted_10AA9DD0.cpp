// Game/Unsorted_10AA9DD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10AA9DD0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6(int* A);
};

class Class_10E6D9BC
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
    virtual void FUN_10aa9dd0(Object_10AA9DD0* p1);

    char Unknown04[0x24];
    int Unknown28;
};

// FUNCTION: 0x10AA9DD0 ?FUN_10aa9dd0@Class_10E6D9BC@@UAEXPAVObject_10AA9DD0@@@Z
void Class_10E6D9BC::FUN_10aa9dd0(Object_10AA9DD0* p1)
{
    if (Unknown28)
        p1->Virtual6(&Unknown28);
}
