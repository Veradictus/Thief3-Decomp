// Game/Unsorted_10919130.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10e49684;

extern float DAT_10eafbdc;

extern float DAT_10f2c8e0;

// FUNCTION: 0x10919130 ?FUN_10919130@@YAXM@Z
void FUN_10919130(float Arg)
{
    DAT_10f2c8e0 = Arg;
    if (Arg > DAT_10e49684)
    {
        DAT_10f2c8e0 = 1.0f;
        return;
    }
    if (Arg < DAT_10eafbdc)
        DAT_10f2c8e0 = 0.0f;
}
