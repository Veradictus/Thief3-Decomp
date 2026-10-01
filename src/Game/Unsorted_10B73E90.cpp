// Game/Unsorted_10B73E90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e878b8[];

extern void* DAT_10e7edb8[];

class Class_10E876D0
{
public:
    Class_10E876D0();

    void** Unknown00;
    char Unknown04[0x114];
    void** Unknown118;
};

class Class_10E878B8 : public Class_10E876D0
{
public:
    Class_10E878B8* FUN_10b73e90();
};

// FUNCTION: 0x10B73E90 ?FUN_10b73e90@Class_10E878B8@@QAEPAV1@XZ
Class_10E878B8* Class_10E878B8::FUN_10b73e90()
{
    this->Class_10E876D0::Class_10E876D0();
    Unknown00 = DAT_10e878b8;
    Unknown118 = DAT_10e7edb8;
    return this;
}
