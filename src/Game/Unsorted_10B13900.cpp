// Game/Unsorted_10B13900.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UT3Game
{
public:
    UT3Game();
};

// FUNCTION: 0x10B15370 ?FUN_10b15370@@YAXPAX@Z
void FUN_10b15370(void* Memory)
{
    new ((EInternal*)Memory) UT3Game();
}
