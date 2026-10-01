// Game/Unsorted_10ACEE60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10ACEE90;

extern Class_10ACEE90* DAT_10f3a40c;

void* FUN_10905c10(int Kind, int* Arg, int A, int B, int C, int D);

// FUNCTION: 0x10ACEE60 ?FUN_10acee60@@YAPAVClass_10ACEE90@@XZ
Class_10ACEE90* FUN_10acee60()
{
    if (!DAT_10f3a40c)
    {
        int Local = 0;
        DAT_10f3a40c = (Class_10ACEE90*)FUN_10905c10(1, &Local, 0, 0, 0, 0);
    }
    return DAT_10f3a40c;
}
