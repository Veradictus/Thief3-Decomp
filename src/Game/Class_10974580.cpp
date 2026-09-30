// Game/Class_10974580.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Target_10974580
{
    char Unknown00[0x218];
    unsigned int Unknown218Bits0To2 : 3;
    unsigned int Unknown218Bit3 : 1;
    unsigned int Unknown218Bits4To31 : 28;
};

struct Holder_10974580
{
    Target_10974580* Unknown00;
};

class Class_10974580
{
public:
    void FUN_10974580(int Value);

    char Unknown00[0x2C];
    Holder_10974580* Unknown2C;
};

// FUNCTION: 0x10974580 ?FUN_10974580@Class_10974580@@QAEXH@Z
void Class_10974580::FUN_10974580(int Value)
{
    Unknown2C->Unknown00->Unknown218Bit3 = Value;
}
