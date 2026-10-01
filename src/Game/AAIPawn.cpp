// Game/AAIPawn.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AAIPawn
{
public:
    AAIPawn();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B97B40 ?InternalConstructor@AAIPawn@@SAXPAX@Z
void AAIPawn::InternalConstructor(void* X)
{
    new ((EInternal*)X) AAIPawn();
}
