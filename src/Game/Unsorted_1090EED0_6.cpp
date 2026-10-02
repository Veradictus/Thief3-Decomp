// Game/Unsorted_1090EED0_6.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0;

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_1090FD40
{
public:
    void FUN_1090f2c0(int Count);
    void FUN_1090fd00();

    int Unknown00;
    int Unknown04;
    Class_109081E0* Unknown08;
};

// FUNCTION: 0x1090FD00 ?FUN_1090fd00@Class_1090FD40@@QAEXXZ
void Class_1090FD40::FUN_1090fd00()
{
    FUN_1090f2c0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
