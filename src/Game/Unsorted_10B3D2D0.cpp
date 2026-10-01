// Game/Unsorted_10B3D2D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7e928[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7E928 : public Class_10B3ACB0
{
public:
    Class_10E7E928* FUN_10b3d2d0();
};

extern void* DAT_10e7e970[];

class Class_10E7E970 : public Class_10B3ACB0
{
public:
    Class_10E7E970* FUN_10b3d2f0();
};

// FUNCTION: 0x10B3D2D0 ?FUN_10b3d2d0@Class_10E7E928@@QAEPAV1@XZ
Class_10E7E928* Class_10E7E928::FUN_10b3d2d0()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7e928;
    return this;
}

// FUNCTION: 0x10B3D2F0 ?FUN_10b3d2f0@Class_10E7E970@@QAEPAV1@XZ
Class_10E7E970* Class_10E7E970::FUN_10b3d2f0()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7e970;
    return this;
}
