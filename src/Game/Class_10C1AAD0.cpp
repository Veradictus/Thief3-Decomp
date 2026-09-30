// Game/Class_10C1AAD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C1AAD0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C1AAD0
{
public:
    bool FUN_10c1aad0(Struct_10C1AAD0* Out, float* Value);

    char Unknown00[0x48];
    Struct_10C1AAD0 Unknown48;
};

// FUNCTION: 0x10C1AAD0 ?FUN_10c1aad0@Class_10C1AAD0@@QAE_NPAUStruct_10C1AAD0@@PAM@Z
bool Class_10C1AAD0::FUN_10c1aad0(Struct_10C1AAD0* Out, float* Value)
{
    *Out = Unknown48;
    *Value = 16.0f;
    return true;
}
