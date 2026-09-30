// Game/Class_10E4B2F8.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4b2f8[];

class Class_10E70A50
{
public:
    Class_10E70A50();

    void** Unknown00;
    char Unknown04[0x28];
};

class Class_10E4B2F8 : public Class_10E70A50
{
public:
    Class_10E4B2F8* FUN_1098cf10();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

// FUNCTION: 0x1098CF10 ?FUN_1098cf10@Class_10E4B2F8@@QAEPAV1@XZ
Class_10E4B2F8* Class_10E4B2F8::FUN_1098cf10()
{
    this->Class_10E70A50::Class_10E70A50();
    UnknownB0 = 0;
    UnknownB4 = 0;
    UnknownB8 = 0;
    Unknown00 = DAT_10e4b2f8;
    return this;
}
