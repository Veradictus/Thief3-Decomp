// Game/Unsorted_10B3D2A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7e8e0[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7E8E0 : public Class_10B3ACB0
{
public:
    Class_10E7E8E0* FUN_10b3d2a0();
};

// FUNCTION: 0x10B3D2A0 ?FUN_10b3d2a0@Class_10E7E8E0@@QAEPAV1@XZ
Class_10E7E8E0* Class_10E7E8E0::FUN_10b3d2a0()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7e8e0;
    return this;
}
