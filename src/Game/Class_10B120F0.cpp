// Game/Class_10B120F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" void* memset(void* Dest, int Value, unsigned int Count);

class Class_10B120F0
{
public:
    Class_10B120F0* FUN_10b120f0();

    int Unknown00;
    int Unknown04[7];
};

// FUNCTION: 0x10B120F0 ?FUN_10b120f0@Class_10B120F0@@QAEPAV1@XZ
Class_10B120F0* Class_10B120F0::FUN_10b120f0()
{
    Unknown00 = 1;
    memset(Unknown04, 0, sizeof(Unknown04));
    return this;
}
