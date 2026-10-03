// Game/Unsorted_10ABC140_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

extern float DAT_10e499a4;

extern "C" double tan(double);

extern "C" double sqrt(double);

extern "C" double cos(double);

// FUNCTION: 0x10ABC440 ?FUN_10abc440@@YAMMMMM@Z
float FUN_10abc440(float A, float B, float C, float D)
{
    float V = C / (2.0f * (A * tan(D) - B));
    if (V < DAT_10eafbdc)
        return DAT_10e499a4;
    return sqrt(V) * A / cos(D);
}
