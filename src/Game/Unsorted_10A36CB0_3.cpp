// Game/Unsorted_10A36CB0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A36CD0
{
    char Unknown00[0x274];
    int Unknown274;
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Struct_10A36CD0* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10A36CD0 ?FUN_10a36cd0@@YAXXZ
void FUN_10a36cd0()
{
    if (DAT_10f35dec->Unknown08)
        DAT_10f35dec->Unknown08->Unknown274++;
}
