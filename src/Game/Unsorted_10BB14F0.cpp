// Game/Unsorted_10BB14F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6CA18
{
public:
    virtual ~Class_10E6CA18() {}
};

class Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D) = 0;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* A, int B, int C, int D);
    virtual void Virtual2(Class_10E5B578* A);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E8DC34 : public Class_10E6CA18, public Class_10E5B578
{
public:
    virtual ~Class_10E8DC34();
    virtual int Virtual0(int A, int B, int C, int* D);
};

// FUNCTION: 0x10BB15D0 ??1Class_10E8DC34@@UAE@XZ
Class_10E8DC34::~Class_10E8DC34()
{
    if (DAT_10f46da0)
        DAT_10f46da0->Virtual2(this);
}
