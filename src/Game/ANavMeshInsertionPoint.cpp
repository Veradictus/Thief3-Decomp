// Game/ANavMeshInsertionPoint.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class ANavMeshInsertionPoint
{
public:
    ANavMeshInsertionPoint();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B95260 ?InternalConstructor@ANavMeshInsertionPoint@@SAXPAX@Z
void ANavMeshInsertionPoint::InternalConstructor(void* X)
{
    new ((EInternal*)X) ANavMeshInsertionPoint();
}
