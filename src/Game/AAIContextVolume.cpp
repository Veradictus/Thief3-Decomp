// Game/AAIContextVolume.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AAIContextVolume
{
public:
    AAIContextVolume();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B95120 ?InternalConstructor@AAIContextVolume@@SAXPAX@Z
void AAIContextVolume::InternalConstructor(void* X)
{
    new ((EInternal*)X) AAIContextVolume();
}
