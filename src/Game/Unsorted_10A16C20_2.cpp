// Game/Unsorted_10A16C20_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A16BC0
{
public:
    void FUN_10a16370(int A);

    char Unknown00[0x18];
};

class Class_10A16BF0
{
public:
    void FUN_10a165c0(int A);

    char Unknown00[0x18];
};

class Class_10E5D688
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
    virtual void FUN_10a16e70();

    char Unknown04[4];
    Class_10A16BC0 Unknown08;
    char Unknown20[0x14];
    Class_10A16BF0 Unknown34;
};

// FUNCTION: 0x10A16E70 ?FUN_10a16e70@Class_10E5D688@@UAEXXZ
void Class_10E5D688::FUN_10a16e70()
{
    Unknown08.FUN_10a16370(0x40);
    Unknown34.FUN_10a165c0(0x40);
}
