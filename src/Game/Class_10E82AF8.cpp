// Game/Class_10E82AF8.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e82af8[];

class Class_10B78780
{
public:
    void FUN_10b78780();

    void** Unknown00;
    char Unknown04[0x18C];
};

class Class_10E82AF8 : public Class_10B78780
{
public:
    Class_10E82AF8* FUN_10b5aea0();

    int Unknown190;
    int Unknown194;
};

// FUNCTION: 0x10B5AEA0 ?FUN_10b5aea0@Class_10E82AF8@@QAEPAV1@XZ
Class_10E82AF8* Class_10E82AF8::FUN_10b5aea0()
{
    FUN_10b78780();
    Unknown190 = 0;
    Unknown194 = 0;
    Unknown00 = DAT_10e82af8;
    return this;
}
