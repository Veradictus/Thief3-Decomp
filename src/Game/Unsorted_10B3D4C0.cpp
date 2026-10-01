// Game/Unsorted_10B3D4C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7ec40[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EC40 : public Class_10B3ACB0
{
public:
    Class_10E7EC40* FUN_10b3d4c0();
};

// FUNCTION: 0x10B3D4C0 ?FUN_10b3d4c0@Class_10E7EC40@@QAEPAV1@XZ
Class_10E7EC40* Class_10E7EC40::FUN_10b3d4c0()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7ec40;
    return this;
}
