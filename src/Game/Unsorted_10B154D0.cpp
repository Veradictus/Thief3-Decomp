// Game/Unsorted_10B154D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Return global pointer with offset - GWindowManager is array of pointers

extern void* GWindowManager[];

// FUNCTION: 0x10B154D0 ?FUN_10b154d0@@YAPAXXZ
void* FUN_10b154d0()
{
    return (char*)GWindowManager[0] + 0x220;
}
