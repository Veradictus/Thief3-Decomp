// Game/Unsorted_10B95160.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AAIPathPoint
{
public:
    AAIPathPoint();
};

// FUNCTION: 0x10B95190 ?FUN_10b95190@@YAXPAX@Z
void FUN_10b95190(void* Memory)
{
    new ((EInternal*)Memory) AAIPathPoint();
}
