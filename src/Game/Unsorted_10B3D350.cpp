// Game/Unsorted_10B3D350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7ea00[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EA00 : public Class_10B3ACB0
{
public:
    Class_10E7EA00* FUN_10b3d350();
};

// FUNCTION: 0x10B3D350 ?FUN_10b3d350@Class_10E7EA00@@QAEPAV1@XZ
Class_10E7EA00* Class_10E7EA00::FUN_10b3d350()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7ea00;
    return this;
}
