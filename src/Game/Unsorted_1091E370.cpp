// Game/Unsorted_1091E370.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_1091E370 {
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_1091E370 {
public:
    char Unknown00[0x34];
    int Unknown34;
    int Unknown38;
    int Unknown3c;
    void FUN_1091e370(const Struct_1091E370* p1);
};

// FUNCTION: 0x1091E370 ?FUN_1091e370@Class_1091E370@@QAEXPBUStruct_1091E370@@@Z
void Class_1091E370::FUN_1091e370(const Struct_1091E370* p1)
{
    Unknown34 = p1->Unknown00;
    Unknown38 = p1->Unknown04;
    Unknown3c = p1->Unknown08;
}
