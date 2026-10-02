// Game/Unsorted_10A589C0_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A58BE0_Member
{
public:
    virtual void Virtual0();
    virtual bool Virtual1();
};

class Class_10E69050
{
public:
    virtual void Virtual0();
    virtual int FUN_10a58bb0();

    char Unknown04[8];
    int Unknown0C;
    int Unknown10;
    Class_10A58BE0_Member** Unknown14;
    int Unknown18;
};

// FUNCTION: 0x10A58BB0 ?FUN_10a58bb0@Class_10E69050@@UAEHXZ
int Class_10E69050::FUN_10a58bb0()
{
    int Index = Unknown18;
    if (Index == Unknown0C - 1)
    {
        if (Unknown14[Index]->Virtual1())
            return 1;
    }
    return 0;
}
