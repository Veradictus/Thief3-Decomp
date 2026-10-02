// Game/Unsorted_10C0BDE0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

struct Item_10C0C150
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C0C150
{
public:
    void FUN_10c0be50(int NewCount);
    void FUN_10c0c050();

    int Unknown00;
    int Unknown04;
    Item_10C0C150* Unknown08;
};

// FUNCTION: 0x10C0C050 ?FUN_10c0c050@Class_10C0C150@@QAEXXZ
void Class_10C0C150::FUN_10c0c050()
{
    FUN_10c0be50(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
