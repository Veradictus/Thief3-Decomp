// Game/Class_10C35670.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C35670
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C35670
{
public:
    void FUN_10c35670(Struct_10C35670* Value);

    char Unknown00[0x68];
    Struct_10C35670 Unknown68;
    char Unknown74[0x27];
    bool Unknown9B;
};

// FUNCTION: 0x10C35670 ?FUN_10c35670@Class_10C35670@@QAEXPAUStruct_10C35670@@@Z
void Class_10C35670::FUN_10c35670(Struct_10C35670* Value)
{
    Unknown68 = *Value;
    Unknown9B = true;
}
