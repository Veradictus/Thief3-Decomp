// Game/Class_10A3D9E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

class Class_10A3D9E0
{
public:
    Class_10AF8250 FUN_10a3d9e0();

    char Unknown00[0x14];
    Class_10AF8250 Unknown14;
};

// FUNCTION: 0x10A3D9E0 ?FUN_10a3d9e0@Class_10A3D9E0@@QAE?AVClass_10AF8250@@XZ
Class_10AF8250 Class_10A3D9E0::FUN_10a3d9e0()
{
    return Class_10AF8250(Unknown14);
}
