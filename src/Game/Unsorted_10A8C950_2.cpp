// Game/Unsorted_10A8C950_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A8C9B0
{
    char Unknown00[0x38];
    int Unknown38;
};

extern int DAT_10f3a1f4;

class Class_10E6C740
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10a8c9b0();

    Struct_10A8C9B0* Unknown04;
};

// FUNCTION: 0x10A8C9B0 ?FUN_10a8c9b0@Class_10E6C740@@UAEHXZ
int Class_10E6C740::FUN_10a8c9b0()
{
    if (Unknown04)
        return DAT_10f3a1f4 > Unknown04->Unknown38;
    return 1;
}
