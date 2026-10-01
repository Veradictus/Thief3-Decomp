// Game/Unsorted_10B4A2A0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e81548[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void* vtable;
};

class Class_10E81548 : public Class_10B3ACB0
{
public:
    char Unknown04[0x10];
    int Unknown14;

    Class_10E81548* FUN_10b4bb40();
};

// FUNCTION: 0x10B4BB40 ?FUN_10b4bb40@Class_10E81548@@QAEPAV1@XZ
Class_10E81548* Class_10E81548::FUN_10b4bb40()
{
    FUN_10b3acb0();
    vtable = DAT_10e81548;
    Unknown14 = 0;
    return this;
}
