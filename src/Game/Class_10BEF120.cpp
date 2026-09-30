// Game/Class_10BEF120.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BEF120
{
public:
    void FUN_10bef120(int Value);

    char Unknown00[0x160];
    int Unknown160;
    int Unknown164;
    int Unknown168;
    int Unknown16C;
    char Unknown170[0x8C];
    int Unknown1FC;
};

// FUNCTION: 0x10BEF120 ?FUN_10bef120@Class_10BEF120@@QAEXH@Z
void Class_10BEF120::FUN_10bef120(int Value)
{
    if (Value != Unknown160)
    {
        Unknown160 = Value;
        Unknown1FC = 0;
        Unknown16C = 0;
        Unknown164 = 0;
    }
}
