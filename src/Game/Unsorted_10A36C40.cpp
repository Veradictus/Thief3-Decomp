// Game/Unsorted_10A36C40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

extern Class_10AF8250 DAT_10f3a00c;

// FUNCTION: 0x10A36C40 ?FUN_10a36c40@@YA?AVClass_10AF8250@@XZ
Class_10AF8250 FUN_10a36c40()
{
    return Class_10AF8250(DAT_10f3a00c);
}
