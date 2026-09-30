// Game/Class_10969de0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10969de0_Field04 {
    char Unknown00[0x3c];
    int Field3c;
};

class Class_10969de0
{
public:
    char Unknown00[0x4];
    Struct_10969de0_Field04* Field04;
    int FUN_10969de0();
};

// FUNCTION: 0x10969DE0 ?FUN_10969de0@Class_10969de0@@QAEHXZ
int Class_10969de0::FUN_10969de0()
{
    return Field04->Field3c;
}
