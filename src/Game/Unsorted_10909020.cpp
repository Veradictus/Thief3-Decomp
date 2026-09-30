// Game/Unsorted_10909020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct _OVERLAPPED;

extern "C" __declspec(dllimport) int __stdcall WriteFile(void* File, const void* Buffer, unsigned long Bytes, unsigned long* Written, _OVERLAPPED* Overlapped);

// FUNCTION: 0x1090E4F0 ?FUN_1090e4f0@@YAHPAXPBXKPAKPAU_OVERLAPPED@@@Z
int FUN_1090e4f0(void* File, const void* Buffer, unsigned long Bytes, unsigned long* Written, _OVERLAPPED* Overlapped)
{
    return WriteFile(File, Buffer, Bytes, Written, Overlapped);
}
