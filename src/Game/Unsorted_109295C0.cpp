// Game/Unsorted_109295C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1092BA00
{
public:
    void FUN_1092ba00(int Param);
};

extern Class_1092BA00 DAT_10eff23c;

extern bool DAT_10f31aa4;

extern int DAT_10f31aa8;

// FUNCTION: 0x1092BB50 ?FUN_1092bb50@@YAXXZ
void FUN_1092bb50()
{
    if (!DAT_10f31aa4)
    {
        DAT_10eff23c.FUN_1092ba00(0x40);
        DAT_10f31aa4 = true;
        DAT_10f31aa8 = 0;
    }
}
