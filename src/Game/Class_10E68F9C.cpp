// Game/Class_10E68F9C.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e68f9c[];

extern void* DAT_10e68f94[];

class Class_10E68F9C
{
public:
    Class_10E68F9C* FUN_10a58420();

    void** Unknown00;        // +0x00: DAT_10e68f9c
    float Unknown04;
    int Unknown08;
    void** Unknown0C;        // +0x0c: DAT_10e68f94
    char Unknown10[0x3C];
    float Unknown4C;
};

// FUNCTION: 0x10A58420 ?FUN_10a58420@Class_10E68F9C@@QAEPAV1@XZ
Class_10E68F9C* Class_10E68F9C::FUN_10a58420()
{
    Unknown04 = 1.0f;
    Unknown08 = 0;
    Unknown00 = DAT_10e68f9c;
    Unknown0C = DAT_10e68f94;
    Unknown4C = 32767.0f;
    return this;
}
