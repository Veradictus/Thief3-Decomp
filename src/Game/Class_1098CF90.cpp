// Game/Class_1098CF90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098CF90
{
public:
    void FUN_1098cf90(Class_1098CF90* Other);

    char Unknown00[0x34];
    Class_1098CF90* Unknown34;
    char Unknown38[0xDC];
    Class_1098CF90* Unknown114;
};

// FUNCTION: 0x1098CF90 ?FUN_1098cf90@Class_1098CF90@@QAEXPAV1@@Z
void Class_1098CF90::FUN_1098cf90(Class_1098CF90* Other)
{
    if (Other->Unknown34)
        Other->Unknown34->Unknown114 = 0;
    Unknown114 = Other;
    Other->Unknown34 = this;
}
