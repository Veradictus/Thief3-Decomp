// Game/Unsorted_10B76270.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e88160;

class Class_10B78780
{
public:
    void FUN_10b78780();

    void** Unknown00;
    char Unknown04[0x18C];
};

class Class_10E88160 : public Class_10B78780
{
public:
    Class_10E88160* FUN_10b762f0();

    int Unknown190;
};

// FUNCTION: 0x10B762F0 ?FUN_10b762f0@Class_10E88160@@QAEPAV1@XZ
Class_10E88160* Class_10E88160::FUN_10b762f0()
{
    FUN_10b78780();
    Unknown00 = &DAT_10e88160;
    Unknown190 = 0;
    return this;
}
