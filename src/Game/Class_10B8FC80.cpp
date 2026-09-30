// Game/Class_10B8FC80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Store global address to field at offset 0 and return this

extern void* DAT_10e89818;

class Class_10B8FC80 {
public:
    void* Field00;
    Class_10B8FC80* FUN_10b8fc80();
};

// FUNCTION: 0x10B8FC80 ?FUN_10b8fc80@Class_10B8FC80@@QAEPAV1@XZ
Class_10B8FC80* Class_10B8FC80::FUN_10b8fc80()
{
    Field00 = &DAT_10e89818;
    return this;
}
