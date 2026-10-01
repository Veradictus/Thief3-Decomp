// Game/Unsorted_10B196B0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10B196B0
{
    char Unknown00[0x1c];
};

struct Data_10B196B0
{
    char Unknown000[0x478];
    Info_10B196B0* Unknown478;
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Data_10B196B0* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10B196B0 ?FUN_10b196b0@@YGPAUInfo_10B196B0@@H@Z
Info_10B196B0* __stdcall FUN_10b196b0(int Index)
{
    return &DAT_10f35dec->Unknown08->Unknown478[Index];
}
