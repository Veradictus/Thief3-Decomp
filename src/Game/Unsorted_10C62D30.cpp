// Game/Unsorted_10C62D30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10C62D30
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
    virtual void Virtual16();
};

class Class_10C62D30
{
public:
    void FUN_10c62d30(Object_10C62D30* A);

    char Unknown00[4];
    Object_10C62D30* Unknown04;
};

// FUNCTION: 0x10C62D30 ?FUN_10c62d30@Class_10C62D30@@QAEXPAVObject_10C62D30@@@Z
void Class_10C62D30::FUN_10c62d30(Object_10C62D30* A)
{
    Object_10C62D30* Old = Unknown04;
    if (Old)
    {
        Old->Virtual16();
        Unknown04 = 0;
    }
    Unknown04 = A;
}
