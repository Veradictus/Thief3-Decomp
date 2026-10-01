// Game/USpawnPoolLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class USpawnPoolLinkDataObject
{
public:
    USpawnPoolLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10AB53F0 ?InternalConstructor@USpawnPoolLinkDataObject@@SAXPAX@Z
void USpawnPoolLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) USpawnPoolLinkDataObject();
}
