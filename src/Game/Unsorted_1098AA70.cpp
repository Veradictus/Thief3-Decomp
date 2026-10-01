// Game/Unsorted_1098AA70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <new>

class UCARDEntry
{
public:
    UCARDEntry();
    void operator delete(void* p);
    static void FUN_1098aca0(void* p);
};

// FUNCTION: 0x1098ACA0 ?FUN_1098aca0@UCARDEntry@@SAXPAX@Z
void UCARDEntry::FUN_1098aca0(void* p)
{
    new (p) UCARDEntry;
}
