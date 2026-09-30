// Game/Class_10B8F700.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Store global address to field at offset 0 and return this

extern void* DAT_10e8980c;

class Class_10B8F700 {
public:
    void* Field00;
    Class_10B8F700* FUN_10b8f700();
};

// FUNCTION: 0x10B8F700 ?FUN_10b8f700@Class_10B8F700@@QAEPAV1@XZ
Class_10B8F700* Class_10B8F700::FUN_10b8f700()
{
    Field00 = &DAT_10e8980c;
    return this;
}
