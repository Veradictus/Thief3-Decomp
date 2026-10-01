// Game/Unsorted_10ABA1A0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10ABB2D0
{
    int Unknown00;
    char Unknown04[0x10];
};

class Class_10E6F47C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int FUN_10abb2d0(int Value);

    char Unknown04[0x10];
    int Unknown14;
    char Unknown18[4];
    Struct_10ABB2D0* Unknown1C;
};

// FUNCTION: 0x10ABB2D0 ?FUN_10abb2d0@Class_10E6F47C@@UAEHH@Z
int Class_10E6F47C::FUN_10abb2d0(int Value)
{
    for (int i = 0; i < Unknown14; i++)
    {
        if (Unknown1C[i].Unknown00 == Value)
            return i;
    }
    return -1;
}
