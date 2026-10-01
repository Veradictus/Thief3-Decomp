// Game/Unsorted_109E3D70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109E44B0
{
    char Unknown00[0x40];
};

extern Struct_109E44B0 DAT_10f2c8e8;

class Class_109E44B0
{
public:
    Struct_109E44B0* FUN_109e44b0();

    char Unknown00[0x118];
    Struct_109E44B0 Unknown118;
};

// FUNCTION: 0x109E44B0 ?FUN_109e44b0@Class_109E44B0@@QAEPAUStruct_109E44B0@@XZ
Struct_109E44B0* Class_109E44B0::FUN_109e44b0()
{
    Unknown118 = DAT_10f2c8e8;
    return &Unknown118;
}
