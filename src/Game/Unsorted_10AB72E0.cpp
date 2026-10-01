// Game/Unsorted_10AB72E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AB7500;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10AB7500* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10AB7500
{
public:
    void FUN_10ab7330();
    void FUN_10ab7500();
};

// FUNCTION: 0x10AB7500 ?FUN_10ab7500@Class_10AB7500@@QAEXXZ
void Class_10AB7500::FUN_10ab7500()
{
    DAT_10f46da0->Virtual1(this, 0x25, -1, -1);
    DAT_10f46da0->Virtual1(this, 0x5a, -1, -1);
    FUN_10ab7330();
}
