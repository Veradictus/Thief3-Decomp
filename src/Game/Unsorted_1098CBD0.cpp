// Game/Unsorted_1098CBD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

// FUNCTION: 0x1098CCE0 ?FUN_1098cce0@@YAMM@Z
float FUN_1098cce0(float A)
{
    int Sign;
    if (A > DAT_10eafbdc)
        Sign = 1;
    else if (A < DAT_10eafbdc)
        Sign = -1;
    else
        Sign = 0;
    return (float)Sign;
}
