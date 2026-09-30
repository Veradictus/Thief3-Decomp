// Game/Class_10E730D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e730d0[];

class Class_10E4E590
{
public:
    Class_10E4E590(int A);

    void** Unknown00;
    char Unknown04[0x28];
    int Unknown2C;
};

class Class_10E730D0 : public Class_10E4E590
{
public:
    Class_10E730D0* FUN_10aee490();

    char Unknown30[4];
    int Unknown34;
    char Unknown38[0x24];
    int Unknown5C;
};

// FUNCTION: 0x10AEE490 ?FUN_10aee490@Class_10E730D0@@QAEPAV1@XZ
Class_10E730D0* Class_10E730D0::FUN_10aee490()
{
    this->Class_10E4E590::Class_10E4E590(0);
    Unknown34 = 1;
    Unknown5C = 0;
    Unknown00 = DAT_10e730d0;
    return this;
}
