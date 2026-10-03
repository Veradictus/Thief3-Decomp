// Game/Unsorted_10C405C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C40730_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10C40730
{
public:
    void FUN_10c40730();

    char Unknown00[0x24];
    Class_10C40730_Member* Unknown24;
};

class Class_10C40740_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10C40740
{
public:
    void FUN_10c40740();

    char Unknown00[0x10];
    Class_10C40740_Member* Unknown10;
};

// FUNCTION: 0x10C40730 ?FUN_10c40730@Class_10C40730@@QAEXXZ
void Class_10C40730::FUN_10c40730()
{
    Class_10C40730_Member* P = Unknown24;
    if (P)
        P->Virtual2();
}
