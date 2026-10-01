// Game/Unsorted_10BECEA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10BEF220_Member
{
    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, void* B, int C, int* D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10BECEA0
{
public:
    void FUN_10becea0(int A);

    char Unknown00[4];
    Struct_10BEF220_Member* Unknown04;
};

// FUNCTION: 0x10BECEA0 ?FUN_10becea0@Class_10BECEA0@@QAEXH@Z
void Class_10BECEA0::FUN_10becea0(int A)
{
    int Value = A;
    DAT_10f46da0->Virtual5(0x56, Unknown04->Unknown08->FUN_10c7d570(), 0, &Value);
}
