// Game/Unsorted_10ACE390.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

// FUNCTION: 0x10ACE450 ?FUN_10ace450@@YGXHHHH@Z
void __stdcall FUN_10ace450(int A, int B, int C, int D)
{
    if (A == 0x10)
        DAT_10f46da0->Virtual5(0x39, B, 0, 0);
}
