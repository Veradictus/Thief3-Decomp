// Game/Class_10C1AF80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C1AF80
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C1AF80
{
public:
    bool FUN_10c1af80(Struct_10C1AF80* Out, float* Value);

    char Unknown00[0xC];
    Struct_10C1AF80 Unknown0C;
};

// FUNCTION: 0x10C1AF80 ?FUN_10c1af80@Class_10C1AF80@@QAE_NPAUStruct_10C1AF80@@PAM@Z
bool Class_10C1AF80::FUN_10c1af80(Struct_10C1AF80* Out, float* Value)
{
    *Out = Unknown0C;
    *Value = 0.0f;
    return true;
}
