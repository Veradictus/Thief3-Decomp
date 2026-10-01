// Game/ACityPopPoint.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class ACityPopPoint
{
public:
    ACityPopPoint();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B95230 ?InternalConstructor@ACityPopPoint@@SAXPAX@Z
void ACityPopPoint::InternalConstructor(void* X)
{
    new ((EInternal*)X) ACityPopPoint();
}
