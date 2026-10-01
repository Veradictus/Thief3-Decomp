// Game/Unsorted_1098E490.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <new>

class AMarker
{
public:
    AMarker();
    void operator delete(void* p);
    static void FUN_1098e490(void* p);
};

// FUNCTION: 0x1098E490 ?FUN_1098e490@AMarker@@SAXPAX@Z
void AMarker::FUN_1098e490(void* p)
{
    new (p) AMarker;
}
