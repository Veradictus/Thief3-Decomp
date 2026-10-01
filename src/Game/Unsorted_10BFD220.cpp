// Game/Unsorted_10BFD220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFD210
{
public:
    float FUN_10bfc3a0();
    void FUN_10bfc680(float Value);
    void FUN_10bfd4c0(float Value);
};

// FUNCTION: 0x10BFD4C0 ?FUN_10bfd4c0@Class_10BFD210@@QAEXM@Z
void Class_10BFD210::FUN_10bfd4c0(float Value)
{
    Value = FUN_10bfc3a0() - Value;
    FUN_10bfc680(Value);
}
