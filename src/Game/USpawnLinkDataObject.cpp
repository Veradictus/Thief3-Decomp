// Game/USpawnLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class USpawnLinkDataObject
{
public:
    USpawnLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1890 ?InternalConstructor@USpawnLinkDataObject@@SAXPAX@Z
void USpawnLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) USpawnLinkDataObject();
}
