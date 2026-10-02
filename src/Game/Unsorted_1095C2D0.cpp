// Game/Unsorted_1095C2D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_1095CAA0
{
    char Unknown00[0xC];
    int Unknown0C;
    int Unknown10;
};

class Class_1095CAA0
{
public:
    bool FUN_1095caa0(Struct_1095CAA0* Other);

    char Unknown00[0x20];
    int Unknown20;
    int Unknown24;
};

// FUNCTION: 0x1095CAA0 ?FUN_1095caa0@Class_1095CAA0@@QAE_NPAUStruct_1095CAA0@@@Z
bool Class_1095CAA0::FUN_1095caa0(Struct_1095CAA0* Other)
{
    if (!Other)
        return false;
    if (Unknown24 >= 0)
        return Other->Unknown10 == Unknown20;
    return Other->Unknown0C == Unknown20;
}
