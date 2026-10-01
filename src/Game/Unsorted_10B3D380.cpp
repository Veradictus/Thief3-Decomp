// Game/Unsorted_10B3D380.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7ea48[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EA48 : public Class_10B3ACB0
{
public:
    Class_10E7EA48* FUN_10b3d380();
};

extern void* DAT_10e7ea90[];

class Class_10E7EA90 : public Class_10B3ACB0
{
public:
    Class_10E7EA90* FUN_10b3d3a0();
};

// FUNCTION: 0x10B3D380 ?FUN_10b3d380@Class_10E7EA48@@QAEPAV1@XZ
Class_10E7EA48* Class_10E7EA48::FUN_10b3d380()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7ea48;
    return this;
}

// FUNCTION: 0x10B3D3A0 ?FUN_10b3d3a0@Class_10E7EA90@@QAEPAV1@XZ
Class_10E7EA90* Class_10E7EA90::FUN_10b3d3a0()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7ea90;
    return this;
}
