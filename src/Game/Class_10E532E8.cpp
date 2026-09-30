// Game/Class_10E532E8.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e532e8[];

class Class_10E70A50
{
public:
    Class_10E70A50();

    void** Unknown00;
    char Unknown04[0x28];
};

class Class_10E532E8 : public Class_10E70A50
{
public:
    Class_10E532E8* FUN_1098d930();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

// FUNCTION: 0x1098D930 ?FUN_1098d930@Class_10E532E8@@QAEPAV1@XZ
Class_10E532E8* Class_10E532E8::FUN_1098d930()
{
    this->Class_10E70A50::Class_10E70A50();
    UnknownB0 = 0;
    UnknownB4 = 0;
    UnknownB8 = 0;
    Unknown00 = DAT_10e532e8;
    return this;
}
