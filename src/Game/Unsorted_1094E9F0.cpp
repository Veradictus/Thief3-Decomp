// Game/Unsorted_1094E9F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_1094E9F0
{
    char Unknown00[4];
    int Unknown04;
};

class Class_10E4AB88
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void FUN_1094e9f0(int p1, int p2);

    char Unknown04[0xF0];
    int Unknown0F4;
    char Unknown0F8[4];
    Struct_1094E9F0** Unknown0FC;
};

// FUNCTION: 0x1094E9F0 ?FUN_1094e9f0@Class_10E4AB88@@UAEXHH@Z
void Class_10E4AB88::FUN_1094e9f0(int p1, int p2)
{
    if (p1 >= Unknown0F4)
        return;
    Unknown0FC[p1]->Unknown04 = p2;
}
