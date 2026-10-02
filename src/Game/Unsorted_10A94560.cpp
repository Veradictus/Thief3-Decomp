// Game/Unsorted_10A94560.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10EB766C
{
public:
    virtual ~Class_10EB766C();

    int Unknown04;
    int Unknown08;
};

class Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D) = 0;
};

class Class_10E6DC88 : public Class_10EB766C, public Class_10E5B578
{
public:
    virtual ~Class_10E6DC88();
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* A, int B, int C, int D);
    virtual void Virtual2(Class_10E5B578* A);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6CD50 : public Class_10E6DC88
{
public:
    virtual ~Class_10E6CD50();
    virtual int Virtual0(int A, int B, int C, int* D);
};

// FUNCTION: 0x10A946E0 ??1Class_10E6CD50@@UAE@XZ
Class_10E6CD50::~Class_10E6CD50()
{
    if (DAT_10f46da0)
        DAT_10f46da0->Virtual2(this);
}
