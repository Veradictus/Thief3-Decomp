// Game/Unsorted_109E4800_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A18FC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int Virtual2();
};

Object_10A18FC0* FUN_10a18fc0();

class Class_109E4800
{
public:
    int FUN_109e4800();

    char Unknown00[0xB0];
    float UnknownB0;
    char UnknownB4[0x18];
    float UnknownCC;
};

// FUNCTION: 0x109E4800 ?FUN_109e4800@Class_109E4800@@QAEHXZ
int Class_109E4800::FUN_109e4800()
{
    float Ratio = (float)FUN_10a18fc0()->Virtual2() / UnknownB0;
    return (int)(Ratio * UnknownCC);
}
