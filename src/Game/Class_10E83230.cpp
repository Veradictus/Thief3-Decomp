// Game/Class_10E83230.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e83230[];

class Class_10E88900
{
public:
    Class_10E88900();

    void** Unknown00;
    char Unknown04[0x2C8];
};

class Class_10E83230 : public Class_10E88900
{
public:
    Class_10E83230* FUN_10b5c400();

    int Unknown2CC;
    int Unknown2D0;
    int Unknown2D4;
};

// FUNCTION: 0x10B5C400 ?FUN_10b5c400@Class_10E83230@@QAEPAV1@XZ
Class_10E83230* Class_10E83230::FUN_10b5c400()
{
    this->Class_10E88900::Class_10E88900();
    Unknown2CC = 0;
    Unknown2D0 = 0;
    Unknown2D4 = 0;
    Unknown00 = DAT_10e83230;
    return this;
}
