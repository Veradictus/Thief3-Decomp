// Game/Unsorted_10B3D320.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7e9b8[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7E9B8 : public Class_10B3ACB0
{
public:
    Class_10E7E9B8* FUN_10b3d320();
};

// FUNCTION: 0x10B3D320 ?FUN_10b3d320@Class_10E7E9B8@@QAEPAV1@XZ
Class_10E7E9B8* Class_10E7E9B8::FUN_10b3d320()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7e9b8;
    return this;
}
