// Game/Class_10E7BB2C.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7bb2c[];

extern void* DAT_10e7b968[];

class Class_10E7BB2C
{
public:
    Class_10E7BB2C* FUN_10b30000();

    void** Unknown00;        // +0x00: DAT_10e7bb2c
    float Unknown04;
    int Unknown08;
    void** Unknown0C;        // +0x0c: DAT_10e7b968
    char Unknown10[0x1C];
    float Unknown2C;
};

// FUNCTION: 0x10B30000 ?FUN_10b30000@Class_10E7BB2C@@QAEPAV1@XZ
Class_10E7BB2C* Class_10E7BB2C::FUN_10b30000()
{
    Unknown04 = 1.0f;
    Unknown08 = 0;
    Unknown00 = DAT_10e7bb2c;
    Unknown0C = DAT_10e7b968;
    Unknown2C = 32767.0f;
    return this;
}
