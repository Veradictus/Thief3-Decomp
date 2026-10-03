// Game/Unsorted_10C63F40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C81D70
{
public:
    virtual void Virtual0();
    virtual bool Virtual1();
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
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual bool Virtual24();

    void FUN_10c81d70(int* A);
};

class Class_10C63F40
{
public:
    void FUN_10c63f40();

    char Unknown00[8];
    Class_10C81D70* Unknown08;
    char Unknown0C[0x14];
    int Unknown20;
};

// FUNCTION: 0x10C63F40 ?FUN_10c63f40@Class_10C63F40@@QAEXXZ
void Class_10C63F40::FUN_10c63f40()
{
    if (!Unknown08->Virtual1() && Unknown08->Virtual24())
        Unknown08->FUN_10c81d70(&Unknown20);
}
