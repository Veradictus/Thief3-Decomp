// Game/Unsorted_10AACF50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f3a370;

extern int DAT_10f3a374;

// FUNCTION: 0x10AAE270 ?FUN_10aae270@@YAXHH@Z
void FUN_10aae270(int A, int B)
{
    if (DAT_10f3a370 == 0 || DAT_10f3a374 == 0)
    {
        DAT_10f3a370 = A;
        DAT_10f3a374 = B;
    }
}
