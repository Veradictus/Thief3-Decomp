// Game/Unsorted_1094E3C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Elem_1094E3A0
{
    char Unknown00[4];
    float Unknown04;
    char Unknown08[0x20];
};

class Class_1094e3a0
{
public:
    char Unknown00[0x108];
    Elem_1094E3A0* Unknown108;
    char Unknown10C[4];
    int Unknown110;

    void FUN_1094e3c0(int Index, float Value);
};

// FUNCTION: 0x1094E3C0 ?FUN_1094e3c0@Class_1094e3a0@@QAEXHM@Z
void Class_1094e3a0::FUN_1094e3c0(int Index, float Value)
{
    Unknown108[Index].Unknown04 = Value;
}
