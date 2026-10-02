// Game/Unsorted_109182E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10e49684;

extern float DAT_10eafbdc;

extern float DAT_10f2c8dc;

// FUNCTION: 0x109190D0 ?FUN_109190d0@@YAXM@Z
void FUN_109190d0(float Arg)
{
    DAT_10f2c8dc = Arg;
    if (Arg > DAT_10e49684)
    {
        DAT_10f2c8dc = 1.0f;
        return;
    }
    if (Arg < DAT_10eafbdc)
        DAT_10f2c8dc = 0.0f;
}
