// Game/Class_109E5310.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109E5310
{
    char Unknown00[0x6C];
    int Unknown6C;
    int Unknown70;
};

class Class_109E5310
{
public:
    void FUN_109e5310(Struct_109E5310* A);
    void FUN_109e3d70();

    char Unknown00[0x98];
    Struct_109E5310* Unknown98;
    char Unknown9C[0x14];
    float UnknownB0;
    float UnknownB4;
};

// FUNCTION: 0x109E5310 ?FUN_109e5310@Class_109E5310@@QAEXPAUStruct_109E5310@@@Z
void Class_109E5310::FUN_109e5310(Struct_109E5310* A)
{
    Unknown98 = A;
    UnknownB0 = (float)A->Unknown6C;
    UnknownB4 = (float)A->Unknown70;
    FUN_109e3d70();
}
