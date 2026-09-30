// Game/Class_10A05FE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

class Class_10A05FE0
{
public:
    Class_10AF8250 FUN_10a05fe0();

    char Unknown00[0x40];
    Class_10AF8250 Unknown40;
};

// FUNCTION: 0x10A05FE0 ?FUN_10a05fe0@Class_10A05FE0@@QAE?AVClass_10AF8250@@XZ
Class_10AF8250 Class_10A05FE0::FUN_10a05fe0()
{
    return Class_10AF8250(Unknown40);
}
