// Game/Unsorted_10C054E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

bool FUN_10c054e0(float A, float B, float C);

// FUNCTION: 0x10C05590 ?FUN_10c05590@@YAHMMM@Z
int FUN_10c05590(float A, float B, float C)
{
    if (FUN_10c054e0(A, B, C))
        return 0;
    return A < B ? -1 : 1;
}
