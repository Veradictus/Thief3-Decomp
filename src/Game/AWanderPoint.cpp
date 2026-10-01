// Game/AWanderPoint.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AWanderPoint
{
public:
    AWanderPoint();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B95240 ?InternalConstructor@AWanderPoint@@SAXPAX@Z
void AWanderPoint::InternalConstructor(void* X)
{
    new ((EInternal*)X) AWanderPoint();
}
