// Game/Class_10E51F30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e51f30[];

class Class_10E70A50
{
public:
    Class_10E70A50();

    void** Unknown00;
    char Unknown04[0x28];
};

class Class_10E51F30 : public Class_10E70A50
{
public:
    Class_10E51F30* FUN_1098dcd0();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

// FUNCTION: 0x1098DCD0 ?FUN_1098dcd0@Class_10E51F30@@QAEPAV1@XZ
Class_10E51F30* Class_10E51F30::FUN_1098dcd0()
{
    this->Class_10E70A50::Class_10E70A50();
    UnknownB0 = 0;
    UnknownB4 = 0;
    UnknownB8 = 0;
    Unknown00 = DAT_10e51f30;
    return this;
}
