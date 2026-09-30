// Game/Class_10C63E90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C63E90
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Data_10C63E90
{
    char Unknown00[0x24];
    Struct_10C63E90 Unknown24;
};

class Class_10C63E90
{
public:
    Struct_10C63E90 FUN_10c63e90();

    char Unknown00[0x8];
    Data_10C63E90* Unknown08;
};

// FUNCTION: 0x10C63E90 ?FUN_10c63e90@Class_10C63E90@@QAE?AUStruct_10C63E90@@XZ
Struct_10C63E90 Class_10C63E90::FUN_10c63e90()
{
    return Unknown08->Unknown24;
}
