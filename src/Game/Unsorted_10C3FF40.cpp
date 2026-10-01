// Game/Unsorted_10C3FF40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C40580_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10C40580
{
public:
    void FUN_10c40580();

    char Unknown00[0x18];
    Class_10C40580_Member* Unknown18;
};

// FUNCTION: 0x10C40580 ?FUN_10c40580@Class_10C40580@@QAEXXZ
void Class_10C40580::FUN_10c40580()
{
    Class_10C40580_Member* P = Unknown18;
    if (P)
        P->Virtual2();
}
