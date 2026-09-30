// Game/Class_10969df0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10969df0_Field04 {
    char Unknown00[0x2c];
    unsigned char Field2c;
};

class Class_10969df0
{
public:
    char Unknown00[0x4];
    Struct_10969df0_Field04* Field04;
    int FUN_10969df0();
};

// FUNCTION: 0x10969DF0 ?FUN_10969df0@Class_10969df0@@QAEHXZ
int Class_10969df0::FUN_10969df0()
{
    return (unsigned char)Field04->Field2c;
}
