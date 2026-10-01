// Game/Unsorted_10A87400.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6c484[];

class Class_10E5D70C
{
public:
    Class_10E5D70C();

    void** Unknown00;
};

class Class_10E6C484 : public Class_10E5D70C
{
public:
    Class_10E6C484* FUN_10a88e30();

    char Unknown04[0x674];
    int Unknown678;
};

// FUNCTION: 0x10A88E30 ?FUN_10a88e30@Class_10E6C484@@QAEPAV1@XZ
Class_10E6C484* Class_10E6C484::FUN_10a88e30()
{
    this->Class_10E5D70C::Class_10E5D70C();
    Unknown00 = DAT_10e6c484;
    Unknown678 = 0;
    return this;
}
