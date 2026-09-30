// Game/Class_10974300.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10974300_Inner {
public:
    char Unknown00[0x4];
    void* Field04;
};

class Class_10974300 {
    char Unknown00[0x2C];
    Class_10974300_Inner* Field2C;
public:
    void* FUN_10974300();
};

// FUNCTION: 0x10974300 ?FUN_10974300@Class_10974300@@QAEPAXXZ
void* Class_10974300::FUN_10974300()
{
    return Field2C->Field04;
}
