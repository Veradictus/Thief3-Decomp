// Game/Unsorted_10930650.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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

class Class_10930A40
{
public:
    void FUN_10930450(int A);
    void FUN_10930a40();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_109329F0
{
public:
    void FUN_109329f0(int Param);
};

extern Class_109329F0 DAT_10eff31c;

extern bool DAT_10f31bb4;

// FUNCTION: 0x10930A40 ?FUN_10930a40@Class_10930A40@@QAEXXZ
void Class_10930A40::FUN_10930a40()
{
    FUN_10930450(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10932B40 ?FUN_10932b40@@YAXXZ
void FUN_10932b40()
{
    if (!DAT_10f31bb4)
    {
        DAT_10eff31c.FUN_109329f0(0x40);
        DAT_10f31bb4 = true;
    }
}
