// Game/Unsorted_10A36BE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

class FString : public Class_10AF8250
{
};

extern FString DAT_10f39ff4;

extern FString DAT_10f3a000;

// FUNCTION: 0x10A36BE0 ?FUN_10a36be0@@YA?AVClass_10AF8250@@XZ
Class_10AF8250 FUN_10a36be0()
{
    return Class_10AF8250(DAT_10f39ff4);
}

// FUNCTION: 0x10A36C00 ?FUN_10a36c00@@YA?AVClass_10AF8250@@XZ
Class_10AF8250 FUN_10a36c00()
{
    return Class_10AF8250(DAT_10f3a000);
}
