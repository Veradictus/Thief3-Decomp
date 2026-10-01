// Game/AAITaggedVolume.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AAITaggedVolume
{
public:
    AAITaggedVolume();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B95130 ?InternalConstructor@AAITaggedVolume@@SAXPAX@Z
void AAITaggedVolume::InternalConstructor(void* X)
{
    new ((EInternal*)X) AAITaggedVolume();
}
