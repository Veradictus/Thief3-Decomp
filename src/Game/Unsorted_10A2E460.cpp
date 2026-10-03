// Game/Unsorted_10A2E460.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10f39f34;

// FUNCTION: 0x10A2E460 ?FUN_10a2e460@@YAXXZ
void FUN_10a2e460()
{
    void* Instance = DAT_10f39f34;
    if (!Instance)
    {
        Instance = new (0, 0, 0, 0, 0) int(-1);
        DAT_10f39f34 = Instance;
    }
}
