// Game/Class_10E888E4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e888e4[];

extern void* DAT_10e68f94[];

class Class_10E888E4
{
public:
    Class_10E888E4* FUN_10b7a2f0();

    void** Unknown00;        // +0x00: DAT_10e888e4
    float Unknown04;
    int Unknown08;
    void** Unknown0C;        // +0x0c: DAT_10e68f94
    char Unknown10[0x3C];
    float Unknown4C;
};

// FUNCTION: 0x10B7A2F0 ?FUN_10b7a2f0@Class_10E888E4@@QAEPAV1@XZ
Class_10E888E4* Class_10E888E4::FUN_10b7a2f0()
{
    Unknown04 = 1.0f;
    Unknown08 = 0;
    Unknown0C = DAT_10e68f94;
    Unknown4C = 32767.0f;
    Unknown00 = DAT_10e888e4;
    return this;
}
