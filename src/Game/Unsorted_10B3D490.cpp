// Game/Unsorted_10B3D490.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7ebf8[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EBF8 : public Class_10B3ACB0
{
public:
    Class_10E7EBF8* FUN_10b3d490();
};

// FUNCTION: 0x10B3D490 ?FUN_10b3d490@Class_10E7EBF8@@QAEPAV1@XZ
Class_10E7EBF8* Class_10E7EBF8::FUN_10b3d490()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7ebf8;
    return this;
}
