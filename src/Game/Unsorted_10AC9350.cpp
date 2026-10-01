// Game/Unsorted_10AC9350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6fd2c[];

class Class_10E6FD2C {
public:
    Class_10E6FD2C* FUN_10aca530();

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C4E880
{
public:
    void FUN_10c4e880(void* Owner);
};

Class_10C4E880* FUN_10c51550();

class Class_10AC9AE0
{
public:
    void FUN_10ac9ae0();

    char Unknown00[4];
    void* Unknown04;
};

// FUNCTION: 0x10AC9AE0 ?FUN_10ac9ae0@Class_10AC9AE0@@QAEXXZ
void Class_10AC9AE0::FUN_10ac9ae0()
{
    if (Unknown04)
    {
        FUN_10c51550()->FUN_10c4e880(Unknown04);
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10ACA530 ?FUN_10aca530@Class_10E6FD2C@@QAEPAV1@XZ
Class_10E6FD2C* Class_10E6FD2C::FUN_10aca530()
{
    Unknown00 = DAT_10e6fd2c;
    Unknown04 = 0;
    Unknown08 = 0;
    return this;
}
