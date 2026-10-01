// Game/Unsorted_10C2E390.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" int __cdecl sprintf(char* Out, const char* Format, ...);

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

struct Struct_10FF66B0
{
    const char* Unknown00;
    char Unknown04[0x10];
};

extern Struct_10FF66B0 DAT_10ff66b0[];

extern const char DAT_10e9aa64[];

class Class_10E9AA38
{
public:
    virtual void Virtual0();
    virtual Class_109081E0 FUN_10c2e690();

    char Unknown04[0x4C];
    int Unknown50;
};

// FUNCTION: 0x10C2E690 ?FUN_10c2e690@Class_10E9AA38@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E9AA38::FUN_10c2e690()
{
    char Buffer[0x34];
    sprintf(Buffer, DAT_10e9aa64, DAT_10ff66b0[Unknown50].Unknown00);
    return Class_109081E0(Buffer);
}
