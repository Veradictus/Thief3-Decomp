// Game/Unsorted_109E4830.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A18FC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3();
};

Object_10A18FC0* FUN_10a18fc0();

class Class_109E4830
{
public:
    int FUN_109e4830();

    char Unknown00[0xB4];
    float UnknownB4;
    char UnknownB8[0x18];
    float UnknownD0;
};

// FUNCTION: 0x109E4830 ?FUN_109e4830@Class_109E4830@@QAEHXZ
int Class_109E4830::FUN_109e4830()
{
    float Ratio = (float)FUN_10a18fc0()->Virtual3() / UnknownB4;
    return (int)(Ratio * UnknownD0);
}
