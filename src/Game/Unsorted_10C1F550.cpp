// Game/Unsorted_10C1F550.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    virtual void Virtual0();
    int FUN_1098e330(int Id, int* Out);
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10FF667C
{
public:
    char Unknown00[0x9C];
    float Unknown9C;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10C1F600
{
public:
    float FUN_10c1f600();

    char Unknown00[4];
    Class_10c7d570* Unknown04;
};

// FUNCTION: 0x10C1F600 ?FUN_10c1f600@Class_10C1F600@@QAEMXZ
float Class_10C1F600::FUN_10c1f600()
{
    float Value = 0.0f;
    if (!((Class_1098E330*)Unknown04->FUN_10c7d570())->FUN_1098e330(0x40100302, (int*)&Value))
        return DAT_10ff667c->Unknown9C;
    return Value * DAT_10ff667c->Unknown9C;
}
