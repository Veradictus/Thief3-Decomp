// Game/Unsorted_10C63EC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C63EC0_Field08
{
    char Unknown00[0xC];
    int Unknown0C;
};

class Class_10C63EC0
{
public:
    char Unknown00[8];
    Struct_10C63EC0_Field08* Unknown08;
    int FUN_10c63ec0();
};

// FUNCTION: 0x10C63EC0 ?FUN_10c63ec0@Class_10C63EC0@@QAEHXZ
int Class_10C63EC0::FUN_10c63ec0()
{
    return Unknown08->Unknown0C;
}
