// Game/Unsorted_10B196D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AA3520_Member
{
    char Unknown00[0x488];
    int Unknown488;
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Struct_10AA3520_Member* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10B19730 ?FUN_10b19730@@YAHXZ
int FUN_10b19730()
{
    return DAT_10f35dec->Unknown08->Unknown488;
}
