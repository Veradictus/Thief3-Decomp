// Game/APatrolPoint.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class APatrolPoint
{
public:
    APatrolPoint();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B95220 ?InternalConstructor@APatrolPoint@@SAXPAX@Z
void APatrolPoint::InternalConstructor(void* X)
{
    new ((EInternal*)X) APatrolPoint();
}
