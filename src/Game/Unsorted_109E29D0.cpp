// Game/Unsorted_109E29D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f35db8;

extern "C" __declspec(dllimport) void __stdcall _RADSetMemory(void* (__stdcall* Alloc)(unsigned), void (__stdcall* Free)(void*));

// FUNCTION: 0x109E29D0 ?FUN_109e29d0@@YAXXZ
void FUN_109e29d0()
{
    if (--DAT_10f35db8 == 0)
        _RADSetMemory(0, 0);
}
