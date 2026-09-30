// Game/Class_10E50700.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e50700[];

class Class_10E4E590
{
public:
    Class_10E4E590(int A);

    void** Unknown00;
    char Unknown04[0x28];
    int Unknown2C;
};

class Class_10E50700 : public Class_10E4E590
{
public:
    Class_10E50700* FUN_10aee540();

    int Unknown30;
    int Unknown34;
    char Unknown38[0x24];
    int Unknown5C;
};

// FUNCTION: 0x10AEE540 ?FUN_10aee540@Class_10E50700@@QAEPAV1@XZ
Class_10E50700* Class_10E50700::FUN_10aee540()
{
    this->Class_10E4E590::Class_10E4E590(0);
    Unknown34 = 1;
    Unknown5C = 0;
    Unknown00 = DAT_10e50700;
    return this;
}
