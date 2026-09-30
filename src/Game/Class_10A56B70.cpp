// Game/Class_10A56B70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

class Class_10A56B70
{
public:
    Class_10AF8250 FUN_10a56b70();

    char Unknown00[0x158];
    Class_10AF8250 Unknown158;
};

// FUNCTION: 0x10A56B70 ?FUN_10a56b70@Class_10A56B70@@QAE?AVClass_10AF8250@@XZ
Class_10AF8250 Class_10A56B70::FUN_10a56b70()
{
    return Class_10AF8250(Unknown158);
}
