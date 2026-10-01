// Game/Unsorted_10B3D430.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7eb68[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
};

class Class_10E7EB68 : public Class_10B3ACB0
{
public:
    Class_10E7EB68* FUN_10b3d430();
};

// FUNCTION: 0x10B3D430 ?FUN_10b3d430@Class_10E7EB68@@QAEPAV1@XZ
Class_10E7EB68* Class_10E7EB68::FUN_10b3d430()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e7eb68;
    return this;
}
