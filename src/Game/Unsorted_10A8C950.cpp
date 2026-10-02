// Game/Unsorted_10A8C950.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f3a1f4;

class Class_10E6C740_Member
{
public:
    char Unknown00[0x38];
    int Unknown38;
};

class Class_10E6C740
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10a8c990();

    Class_10E6C740_Member* Unknown04;
};

// FUNCTION: 0x10A8C990 ?FUN_10a8c990@Class_10E6C740@@UAEXXZ
void Class_10E6C740::FUN_10a8c990()
{
    if (Unknown04 && DAT_10f3a1f4 <= Unknown04->Unknown38)
        DAT_10f3a1f4++;
}
