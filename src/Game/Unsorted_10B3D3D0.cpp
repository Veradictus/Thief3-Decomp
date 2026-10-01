// Game/Unsorted_10B3D3D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7ead8[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EAD8 : public Class_10B3ACB0
{
public:
    Class_10E7EAD8* FUN_10b3d3d0();
};

// FUNCTION: 0x10B3D3D0 ?FUN_10b3d3d0@Class_10E7EAD8@@QAEPAV1@XZ
Class_10E7EAD8* Class_10E7EAD8::FUN_10b3d3d0()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7ead8;
    return this;
}
