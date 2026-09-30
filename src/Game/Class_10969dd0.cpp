// Game/Class_10969dd0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10969dd0_Field04 {
    char Unknown00[0x38];
    int Field38;
};

class Class_10969dd0
{
public:
    char Unknown00[0x4];
    Struct_10969dd0_Field04* Field04;
    int FUN_10969dd0();
};

// FUNCTION: 0x10969DD0 ?FUN_10969dd0@Class_10969dd0@@QAEHXZ
int Class_10969dd0::FUN_10969dd0()
{
    return Field04->Field38;
}
