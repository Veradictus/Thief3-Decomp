// Game/Unsorted_10C13CD0_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E5B578
{
public:
    virtual void Virtual0() = 0;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* Listener, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6DC88_Primary
{
public:
    virtual void FUN_10ba38f0();

    char Unknown04[8];
};

class Class_10E6DC88 : public Class_10E6DC88_Primary, public Class_10E5B578
{
public:
    int Unknown10;
};

class Class_10E8C194 : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10c13e50();
};

// FUNCTION: 0x10C13E50 ?FUN_10c13e50@Class_10E8C194@@UAEXXZ
void Class_10E8C194::FUN_10c13e50()
{
    DAT_10f46da0->Virtual1(this, 0x51, -1, -1);
}
