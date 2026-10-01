// Game/Unsorted_10AA8060.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA8220_Param
{
public:
    virtual void Virtual0(void* Value);
};

class Class_10E6C194
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10aa8220(Class_10AA8220_Param* A);

    char Unknown04[4];
};

// FUNCTION: 0x10AA8220 ?FUN_10aa8220@Class_10E6C194@@UAEHPAVClass_10AA8220_Param@@@Z
int Class_10E6C194::FUN_10aa8220(Class_10AA8220_Param* A)
{
    A->Virtual0(&Unknown04);
    return 1;
}
