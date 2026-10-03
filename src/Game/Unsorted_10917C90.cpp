// Game/Unsorted_10917C90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6D8F0
{
public:
    virtual void FUN_10aa69e0();
    virtual void FUN_10c3e130(int Value);
};

class Class_109242E0 : public Class_10E6D8F0
{
};

struct Struct_10917D20
{
    int Unknown00[16];
};

class Class_1091E940
{
public:
    void FUN_1091e940(int A, int B);

    int Unknown00;
    Struct_10917D20 Unknown04;
    char Unknown44[0x13C];
    float Unknown180;
    int Unknown184;
};

extern Class_1091E940* DAT_10f2c738;

extern Class_109242E0* DAT_10f319a0;

// FUNCTION: 0x10917D20 ?FUN_10917d20@@YAXPBUStruct_10917D20@@MHH@Z
void FUN_10917d20(const Struct_10917D20* Matrix, float A, int B, int C)
{
    if (DAT_10f2c738)
    {
        DAT_10f2c738->Unknown184 = B;
        DAT_10f2c738->Unknown180 = A;
        DAT_10f2c738->Unknown04 = *Matrix;
        DAT_10f2c738->FUN_1091e940(C, 1);
        DAT_10f319a0->Class_10E6D8F0::FUN_10c3e130((int)DAT_10f2c738);
    }
}
