// Game/Unsorted_10BDF460.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BDF610
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E95288
{
public:
    void FUN_10bdf610(Struct_10BDF610* A, float B, float C, float D, float E, unsigned char F);

    char Unknown00[0x48];
    Struct_10BDF610 Unknown48;
    float Unknown54;
    float Unknown58;
    float Unknown5C;
    float Unknown60;
    char Unknown64[4];
    unsigned char Unknown68;
};

// FUNCTION: 0x10BDF610 ?FUN_10bdf610@Class_10E95288@@QAEXPAUStruct_10BDF610@@MMMME@Z
void Class_10E95288::FUN_10bdf610(Struct_10BDF610* A, float B, float C, float D, float E, unsigned char F)
{
    Unknown48 = *A;
    Unknown54 = B;
    Unknown58 = C;
    Unknown5C = D;
    Unknown60 = E;
    Unknown68 = F;
}
