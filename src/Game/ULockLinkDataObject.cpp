// Game/ULockLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class ULockLinkDataObject
{
public:
    ULockLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10AB53C0 ?InternalConstructor@ULockLinkDataObject@@SAXPAX@Z
void ULockLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) ULockLinkDataObject();
}
