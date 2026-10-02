// Game/Unsorted_10B398B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B21560
{
public:
    unsigned char FUN_10b21560();
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Class_10B21560* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10B39AB0
{
public:
    float FUN_10b39ab0();

    char Unknown00[0xC];
    float Unknown0C;
    char Unknown10[0xC];
    float Unknown1C;
};

// FUNCTION: 0x10B39AB0 ?FUN_10b39ab0@Class_10B39AB0@@QAEMXZ
float Class_10B39AB0::FUN_10b39ab0()
{
    if (!DAT_10f35dec->Unknown08->FUN_10b21560())
        return Unknown0C;
    return Unknown1C;
}
