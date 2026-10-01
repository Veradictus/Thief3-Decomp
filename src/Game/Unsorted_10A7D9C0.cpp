// Game/Unsorted_10A7D9C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6bea0[];

class Class_10E6BEA0;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6BEA0* Obj, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6BEA0
{
public:
    Class_10E6BEA0* FUN_10a7da70();

    void** Unknown00;
};

// FUNCTION: 0x10A7DA70 ?FUN_10a7da70@Class_10E6BEA0@@QAEPAV1@XZ
Class_10E6BEA0* Class_10E6BEA0::FUN_10a7da70()
{
    Unknown00 = DAT_10e6bea0;
    DAT_10f46da0->Virtual1(this, 0x27, -1, -1);
    return this;
}
