// Game/Unsorted_10B56CB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e82058;

extern void* DAT_10e7edb8[];

class Class_10E67BD8
{
public:
    Class_10E67BD8();

    void* vtable;
};

class Class_10E82058 : public Class_10E67BD8
{
public:
    char Unknown04[0x114];
    void** Unknown118;

    Class_10E82058* FUN_10b592a0();
};

// FUNCTION: 0x10B592A0 ?FUN_10b592a0@Class_10E82058@@QAEPAV1@XZ
Class_10E82058* Class_10E82058::FUN_10b592a0()
{
    this->Class_10E67BD8::Class_10E67BD8();
    vtable = &DAT_10e82058;
    Unknown118 = DAT_10e7edb8;
    return this;
}
