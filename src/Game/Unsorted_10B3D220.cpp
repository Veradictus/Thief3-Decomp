// Game/Unsorted_10B3D220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7e808[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7E808 : public Class_10B3ACB0
{
public:
    Class_10E7E808* FUN_10b3d220();
};

extern void* DAT_10e7e850[];

class Class_10E7E850 : public Class_10B3ACB0
{
public:
    Class_10E7E850* FUN_10b3d240();
};

// FUNCTION: 0x10B3D220 ?FUN_10b3d220@Class_10E7E808@@QAEPAV1@XZ
Class_10E7E808* Class_10E7E808::FUN_10b3d220()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7e808;
    return this;
}

// FUNCTION: 0x10B3D240 ?FUN_10b3d240@Class_10E7E850@@QAEPAV1@XZ
Class_10E7E850* Class_10E7E850::FUN_10b3d240()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7e850;
    return this;
}
