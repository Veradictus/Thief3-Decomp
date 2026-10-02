// Game/Unsorted_10C13F10_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E8C2A4 : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10c14140();
};

class Class_10E8C2C4 : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10c14210();
};

// FUNCTION: 0x10C14140 ?FUN_10c14140@Class_10E8C2A4@@UAEXXZ
void Class_10E8C2A4::FUN_10c14140()
{
    DAT_10f46da0->Virtual1(this, 0x55, -1, -1);
}

// FUNCTION: 0x10C14210 ?FUN_10c14210@Class_10E8C2C4@@UAEXXZ
void Class_10E8C2C4::FUN_10c14210()
{
    DAT_10f46da0->Virtual1(this, 0x10, -1, -1);
}
