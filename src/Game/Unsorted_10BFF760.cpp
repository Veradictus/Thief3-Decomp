// Game/Unsorted_10BFF760.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

float FUN_10c05bc0(int A, int B, int C, float D);

// FUNCTION: 0x10C003A0 ?FUN_10c003a0@@YAHHHH@Z
int FUN_10c003a0(int A, int B, int C)
{
    if (FUN_10c05bc0(A, B, C, 1.0f) > DAT_10eafbdc)
        return 1;
    return 0;
}
