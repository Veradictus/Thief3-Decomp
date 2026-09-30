// Game/Class_10C168F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10c00480();

class Class_10C168F0
{
public:
    void FUN_10c168f0(int A, float B);

    char Unknown00[0xAC];
    int Unknown0AC;
    float Unknown0B0;
};

// FUNCTION: 0x10C168F0 ?FUN_10c168f0@Class_10C168F0@@QAEXHM@Z
void Class_10C168F0::FUN_10c168f0(int A, float B)
{
    Unknown0AC = A;
    Unknown0B0 = FUN_10c00480() + B;
}
