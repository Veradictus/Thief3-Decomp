// Game/Unsorted_10BD1B40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10bd1900();

double FUN_10c00480();

class Class_10BE3FF0
{
public:
    void FUN_10be3ff0();
};

class Class_10BB89D0
{
public:
    Class_10BE3FF0* FUN_10bb89d0();
    void FUN_10bbc0f0(int A);

    char Unknown00[0x33C];
    float Unknown33C;
};

class Class_10E93878
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void FUN_10bd1bc0();

    Class_10BB89D0* Unknown04;
    char Unknown08[4];
    float Unknown0C;
    char Unknown10[0x40];
    unsigned char Unknown50;
};

// FUNCTION: 0x10BD1BC0 ?FUN_10bd1bc0@Class_10E93878@@UAEXXZ
void Class_10E93878::FUN_10bd1bc0()
{
    FUN_10bd1900();
    if (!(FUN_10c00480() - Unknown0C < 10.0) && Unknown50 >= 7)
        Unknown04->FUN_10bb89d0()->FUN_10be3ff0();
}
