// Game/Unsorted_10BA9030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E8D65C
{
public:
    virtual void Virtual0();
    virtual bool Virtual1();
    virtual void Virtual2();
    virtual void FUN_10ba9030(int Value);
    virtual void FUN_10ba9010(bool p1);

    char Unknown04;
    bool Unknown05;
    char Unknown06[6];
    int Unknown0C;
};

// FUNCTION: 0x10BA9030 ?FUN_10ba9030@Class_10E8D65C@@UAEXH@Z
void Class_10E8D65C::FUN_10ba9030(int Value)
{
    if (Virtual1() && Unknown0C == Value)
        FUN_10ba9010(false);
}
