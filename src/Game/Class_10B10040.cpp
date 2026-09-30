// Game/Class_10B10040.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Store global address to field at offset 0 - return this

extern void* DAT_10e7796c;

class Class_10B10040 {
public:
    void* Field00;
    Class_10B10040* FUN_10b10040();
};

// FUNCTION: 0x10B10040 ?FUN_10b10040@Class_10B10040@@QAEPAV1@XZ
Class_10B10040* Class_10B10040::FUN_10b10040()
{
    Field00 = &DAT_10e7796c;
    return this;
}
