// Game/Class_10E816E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e816e0[];

class Class_10B3ACB0
{
public:
    void FUN_10b3acb0();

    void** Unknown00;
    char Unknown04[0x0C];
};

class Class_10E816E0 : public Class_10B3ACB0
{
public:
    Class_10E816E0* FUN_10b53a30();

    char Unknown10[0x10];
    int Unknown20;
    int Unknown24;
    float Unknown28;
};

// FUNCTION: 0x10B53A30 ?FUN_10b53a30@Class_10E816E0@@QAEPAV1@XZ
Class_10E816E0* Class_10E816E0::FUN_10b53a30()
{
    FUN_10b3acb0();
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown00 = DAT_10e816e0;
    Unknown28 = -1.0f;
    return this;
}
