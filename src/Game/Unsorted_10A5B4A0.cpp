// Game/Unsorted_10A5B4A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e696a8[];

class Class_10E6B078
{
public:
    Class_10E6B078();

    void** Unknown00;
    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0xCC];
};

class Class_10E696A8 : public Class_10E6B078
{
public:
    Class_10E696A8* FUN_10a5d3c0();

    int Unknown1B8;
    int Unknown1BC;
    int Unknown1C0;
    int Unknown1C4;
    int Unknown1C8;
};

// FUNCTION: 0x10A5D3C0 ?FUN_10a5d3c0@Class_10E696A8@@QAEPAV1@XZ
Class_10E696A8* Class_10E696A8::FUN_10a5d3c0()
{
    this->Class_10E6B078::Class_10E6B078();
    Unknown1B8 = 0;
    Unknown1BC = 0;
    Unknown1C0 = 0;
    Unknown1C4 = 0;
    Unknown1C8 = 0;
    Unknown00 = DAT_10e696a8;
    Unknown0E8 = 6;
    return this;
}
