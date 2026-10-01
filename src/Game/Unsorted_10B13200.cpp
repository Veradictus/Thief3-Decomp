// Game/Unsorted_10B13200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AGarrett
{
public:
    AGarrett();
};

class UT3GameEngine
{
public:
    UT3GameEngine();
};

// FUNCTION: 0x10B13550 ?FUN_10b13550@@YAXPAX@Z
void FUN_10b13550(void* Memory)
{
    new ((EInternal*)Memory) AGarrett();
}

// FUNCTION: 0x10B136E0 ?FUN_10b136e0@@YAXPAX@Z
void FUN_10b136e0(void* Memory)
{
    new ((EInternal*)Memory) UT3GameEngine();
}
