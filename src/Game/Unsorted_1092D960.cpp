// Game/Unsorted_1092D960.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1092F100;

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    Class_1092F100** Unknown08;
};

class Class_1092F100
{
public:
    void FUN_1092f100();
};

extern Class_10BFBD70 DAT_10f31b9c;

struct Struct_1092FCA0
{
    char Unknown00[0x38];
    int Unknown38;
};

// FUNCTION: 0x1092F100 ?FUN_1092f100@Class_1092F100@@QAEXXZ
void Class_1092F100::FUN_1092f100()
{
    int Index = DAT_10f31b9c.Unknown00;
    DAT_10f31b9c.FUN_10bfbd70(DAT_10f31b9c.Unknown00 + 1);
    DAT_10f31b9c.Unknown08[Index] = this;
}

// FUNCTION: 0x1092FCA0 ?FUN_1092fca0@@YAHPAUStruct_1092FCA0@@0@Z
int FUN_1092fca0(Struct_1092FCA0* a, Struct_1092FCA0* b)
{
    return a->Unknown38 - b->Unknown38;
}
