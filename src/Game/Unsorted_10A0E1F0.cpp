// Game/Unsorted_10A0E1F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10f3986c;

void* FUN_10905c10(int Kind, int* Arg, int A, int B, int C, int D);

// FUNCTION: 0x10A0E1F0 ?FUN_10a0e1f0@@YAXXZ
void FUN_10a0e1f0()
{
    if (DAT_10f3986c == 0)
    {
        int Value = 0;
        DAT_10f3986c = FUN_10905c10(1, &Value, 0, 0, 0, 0);
    }
}
