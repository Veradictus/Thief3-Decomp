// Game/Unsorted_10B3D460.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7ebb0[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EBB0 : public Class_10B3ACB0
{
public:
    Class_10E7EBB0* FUN_10b3d460();
};

// FUNCTION: 0x10B3D460 ?FUN_10b3d460@Class_10E7EBB0@@QAEPAV1@XZ
Class_10E7EBB0* Class_10E7EBB0::FUN_10b3d460()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7ebb0;
    return this;
}
