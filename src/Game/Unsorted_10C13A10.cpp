// Game/Unsorted_10C13A10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    virtual void Virtual1();
    virtual void Virtual2(Class_10E5B578* Listener);
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
    ~Class_10E6DC88();
};

class Class_10E8C2E4 : public Class_10E6DC88
{
public:
    ~Class_10E8C2E4();

    virtual void Virtual0();
};

// FUNCTION: 0x10C13A10 ??1Class_10E8C2E4@@QAE@XZ
Class_10E8C2E4::~Class_10E8C2E4()
{
    DAT_10f46da0->Virtual2(this);
}
