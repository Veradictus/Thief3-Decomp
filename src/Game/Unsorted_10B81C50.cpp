// Game/Unsorted_10B81C50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D9FEE0
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
    virtual void Virtual13(int A);

    void FUN_10d9fee0(int A, int B);
};

class Class_10B81CC0
{
public:
    void FUN_10b81cc0();

    char Unknown00[0x10];
    Class_10D9FEE0* Unknown10;
    char Unknown14[0x10C];
    bool Unknown120;
};

// FUNCTION: 0x10B81CC0 ?FUN_10b81cc0@Class_10B81CC0@@QAEXXZ
void Class_10B81CC0::FUN_10b81cc0()
{
    Unknown120 = false;
    Unknown10->Virtual13(1);
    Unknown10->FUN_10d9fee0(0, 1);
}
