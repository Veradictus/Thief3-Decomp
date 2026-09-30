// Game/Class_10E72E48.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e72e48[];

class Class_10E4E590
{
public:
    Class_10E4E590(int A);

    void** Unknown00;
    char Unknown04[0x28];
    int Unknown2C;
};

class Class_10E72E48 : public Class_10E4E590
{
public:
    Class_10E72E48* FUN_10aee460();

    char Unknown30[4];
    int Unknown34;
    char Unknown38[0x24];
    int Unknown5C;
};

// FUNCTION: 0x10AEE460 ?FUN_10aee460@Class_10E72E48@@QAEPAV1@XZ
Class_10E72E48* Class_10E72E48::FUN_10aee460()
{
    this->Class_10E4E590::Class_10E4E590(0);
    Unknown34 = 1;
    Unknown5C = 0;
    Unknown00 = DAT_10e72e48;
    return this;
}
