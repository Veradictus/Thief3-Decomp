// Game/Class_10CBCAC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10CBCAC0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

class Class_10CBCAC0
{
public:
    void FUN_10cbcac0(Struct_10CBCAC0* In);

    char Unknown00[0x8];
    int Unknown08;
    char Unknown0C[0x44];
    int Unknown50;
    int Unknown54;
    int Unknown58;
    int Unknown5C;
};

// FUNCTION: 0x10CBCAC0 ?FUN_10cbcac0@Class_10CBCAC0@@QAEXPAUStruct_10CBCAC0@@@Z
void Class_10CBCAC0::FUN_10cbcac0(Struct_10CBCAC0* In)
{
    Unknown50 = In->Unknown04;
    Unknown54 = In->Unknown08;
    Unknown58 = In->Unknown0C;
    Unknown5C = In->Unknown10;
    Unknown08 = In->Unknown00;
}
