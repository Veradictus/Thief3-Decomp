// Game/UT3GameRegistrar.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UT3GameRegistrar
{
public:
    UT3GameRegistrar();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10AB3D50 ?InternalConstructor@UT3GameRegistrar@@SAXPAX@Z
void UT3GameRegistrar::InternalConstructor(void* X)
{
    new ((EInternal*)X) UT3GameRegistrar();
}
