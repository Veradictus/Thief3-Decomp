// Game/Unsorted_10AC9440.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AC98B0
{
public:
    void FUN_10ac9840();
    void FUN_10ac98b0();

    char Unknown00[0x4];
    bool Unknown04;
};

extern void* DAT_10e6fd1c[];

class Class_10E6FD1C
{
public:
    Class_10E6FD1C* FUN_10ac9ac0();

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    char Unknown18;
};

// FUNCTION: 0x10AC98B0 ?FUN_10ac98b0@Class_10AC98B0@@QAEXXZ
void Class_10AC98B0::FUN_10ac98b0()
{
    if (Unknown04)
        FUN_10ac9840();
}

// FUNCTION: 0x10AC9AC0 ?FUN_10ac9ac0@Class_10E6FD1C@@QAEPAV1@XZ
Class_10E6FD1C* Class_10E6FD1C::FUN_10ac9ac0()
{
    Unknown00 = DAT_10e6fd1c;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    return this;
}
