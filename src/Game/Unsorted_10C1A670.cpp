// Game/Unsorted_10C1A670.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int* Obj);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10C1A690
{
public:
    void FUN_10c1a690();

    char Unknown00[4];
    int* Unknown04;
};

// FUNCTION: 0x10C1A690 ?FUN_10c1a690@Class_10C1A690@@QAEXXZ
void Class_10C1A690::FUN_10c1a690()
{
    if (Unknown04)
    {
        int* Obj = Unknown04 - 1;
        FUN_10905aa0()->Virtual5(Obj);
        Unknown04 = 0;
    }
}
