// Game/Unsorted_10B19740.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B19740_Item
{
    char Unknown00[0x1c];
};

struct Struct_10AA3520_Member
{
    char Unknown00[0x484];
    Struct_10B19740_Item* Unknown484;
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Struct_10AA3520_Member* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10B19740 ?FUN_10b19740@@YGPAUStruct_10B19740_Item@@H@Z
Struct_10B19740_Item* __stdcall FUN_10b19740(int Index)
{
    return &DAT_10f35dec->Unknown08->Unknown484[Index];
}
