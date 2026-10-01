// Game/Unsorted_10B3D400.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7eb20[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EB20 : public Class_10B3ACB0
{
public:
    Class_10E7EB20* FUN_10b3d400();
};

// FUNCTION: 0x10B3D400 ?FUN_10b3d400@Class_10E7EB20@@QAEPAV1@XZ
Class_10E7EB20* Class_10E7EB20::FUN_10b3d400()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7eb20;
    return this;
}
