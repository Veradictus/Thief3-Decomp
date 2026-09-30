// Game/Class_10E7AE9C.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7ae9c[];

extern void* DAT_10e6f614[];

class Class_10E7AE9C
{
public:
    Class_10E7AE9C* FUN_10b29810();

    void** Unknown00;        // +0x00: DAT_10e7ae9c
    float Unknown04;
    int Unknown08;
    void** Unknown0C;        // +0x0c: DAT_10e6f614
    char Unknown10[0x3C];
    float Unknown4C;
};

// FUNCTION: 0x10B29810 ?FUN_10b29810@Class_10E7AE9C@@QAEPAV1@XZ
Class_10E7AE9C* Class_10E7AE9C::FUN_10b29810()
{
    Unknown04 = 1.0f;
    Unknown08 = 0;
    Unknown0C = DAT_10e6f614;
    Unknown4C = 32767.0f;
    Unknown00 = DAT_10e7ae9c;
    return this;
}
