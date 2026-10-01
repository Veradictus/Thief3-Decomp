// Game/Unsorted_10A69180.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A697A0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
    float Unknown0C;
    float Unknown10;
    float Unknown14;
    float Unknown18;
    float Unknown1C;
    float Unknown20;
    float Unknown24;
    float Unknown28;
    float Unknown2C;
};

extern void* DAT_10e6b614[];

class Class_10E6B614;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6B614* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6B614
{
public:
    Class_10E6B614* FUN_10a69540();

    void** Unknown00;
};

// FUNCTION: 0x10A69540 ?FUN_10a69540@Class_10E6B614@@QAEPAV1@XZ
Class_10E6B614* Class_10E6B614::FUN_10a69540()
{
    Unknown00 = DAT_10e6b614;
    DAT_10f46da0->Virtual1(this, 0x25, -1, -1);
    DAT_10f46da0->Virtual1(this, 0x24, -1, -1);
    return this;
}

// FUNCTION: 0x10A697A0 ?FUN_10a697a0@@YAXPAUStruct_10A697A0@@@Z
void FUN_10a697a0(Struct_10A697A0* Out)
{
    Out->Unknown00 = 0.8f;
    Out->Unknown04 = 1.0f;
    Out->Unknown08 = 0.01f;
    Out->Unknown0C = 0.0f;
    Out->Unknown10 = 0.25f;
    Out->Unknown14 = 0.25f;
    Out->Unknown18 = 0.0f;
    Out->Unknown1C = 0.5f;
    Out->Unknown20 = 5.0f;
    Out->Unknown24 = 6.0f;
    Out->Unknown28 = 1.0f;
    Out->Unknown2C = 1.0f;
}
