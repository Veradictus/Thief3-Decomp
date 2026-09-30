// Game/Class_10C1AD20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C1AD20
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C1AD20
{
public:
    bool FUN_10c1ad20(Struct_10C1AD20* Out, float* Value);

    char Unknown00[0x48];
    Struct_10C1AD20 Unknown48;
};

// FUNCTION: 0x10C1AD20 ?FUN_10c1ad20@Class_10C1AD20@@QAE_NPAUStruct_10C1AD20@@PAM@Z
bool Class_10C1AD20::FUN_10c1ad20(Struct_10C1AD20* Out, float* Value)
{
    *Out = Unknown48;
    *Value = 0.0f;
    return true;
}
