// Game/Unsorted_10AA63D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6d8cc[];

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10BFBD70
{
public:
    ~Class_10BFBD70()
    {
        FUN_10bfbd70(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10E6D8CC
{
public:
    void FUN_10aa63f0();

    void** VTable;
    Class_10BFBD70 Unknown04;
    int Unknown10;
};

// FUNCTION: 0x10AA63F0 ?FUN_10aa63f0@Class_10E6D8CC@@QAEXXZ
void Class_10E6D8CC::FUN_10aa63f0()
{
    VTable = DAT_10e6d8cc;
    Unknown04.~Class_10BFBD70();
}
