// Game/Unsorted_10A68BB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10953AC0
{
public:
    void FUN_10953ac0(int p1);
};

class Class_10E6B5A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void FUN_10a68bf0(int p1);

    char Unknown04[0xC];
    int Unknown10;
    Class_10953AC0 Unknown14;
};

// FUNCTION: 0x10A68BF0 ?FUN_10a68bf0@Class_10E6B5A0@@UAEXH@Z
void Class_10E6B5A0::FUN_10a68bf0(int p1)
{
    Unknown14.FUN_10953ac0(p1);
    Unknown10++;
}
