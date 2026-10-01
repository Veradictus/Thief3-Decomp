// Game/Unsorted_10B3E240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7edb8[];

extern void* DAT_10e7edc0[];

class Class_10E69080
{
public:
    Class_10E69080();

    void** Unknown00;
    char Unknown04[0x114];
    void** Unknown118;
    char Unknown11C[0xB4];
};

class Class_10E7EDC0 : public Class_10E69080
{
public:
    Class_10E7EDC0* FUN_10b3fd90();

    char Unknown1D0;
    char Unknown1D1;
};

// FUNCTION: 0x10B3FD90 ?FUN_10b3fd90@Class_10E7EDC0@@QAEPAV1@XZ
Class_10E7EDC0* Class_10E7EDC0::FUN_10b3fd90()
{
    this->Class_10E69080::Class_10E69080();
    Unknown1D0 = 1;
    Unknown1D1 = 1;
    Unknown00 = DAT_10e7edc0;
    Unknown118 = DAT_10e7edb8;
    return this;
}
