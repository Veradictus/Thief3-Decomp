// Game/Class_109987E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109987E0
{
public:
    void FUN_109987e0(float A);
    void FUN_10998730(float A);

    char Unknown00[0xE4];
    float Unknown0E4;
    char Unknown0E8[0xC];
    float Unknown0F4;
    char Unknown0F8[0x64];
    int Unknown15C;
};

// FUNCTION: 0x109987E0 ?FUN_109987e0@Class_109987E0@@QAEXM@Z
void Class_109987E0::FUN_109987e0(float A)
{
    Unknown0F4 = A;
    Unknown15C = 0;
    FUN_10998730(A / Unknown0E4);
}
