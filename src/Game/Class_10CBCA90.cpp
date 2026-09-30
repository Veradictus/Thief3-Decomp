// Game/Class_10CBCA90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10CBCA90
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

class Class_10CBCA90
{
public:
    void FUN_10cbca90(Struct_10CBCA90* Out);

    char Unknown00[0x8];
    int Unknown08;
    char Unknown0C[0x44];
    int Unknown50;
    int Unknown54;
    int Unknown58;
    int Unknown5C;
};

// FUNCTION: 0x10CBCA90 ?FUN_10cbca90@Class_10CBCA90@@QAEXPAUStruct_10CBCA90@@@Z
void Class_10CBCA90::FUN_10cbca90(Struct_10CBCA90* Out)
{
    Out->Unknown04 = Unknown50;
    Out->Unknown08 = Unknown54;
    Out->Unknown0C = Unknown58;
    Out->Unknown10 = Unknown5C;
    Out->Unknown00 = Unknown08;
}
