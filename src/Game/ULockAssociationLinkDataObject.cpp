// Game/ULockAssociationLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class ULockAssociationLinkDataObject
{
public:
    ULockAssociationLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A17C0 ?InternalConstructor@ULockAssociationLinkDataObject@@SAXPAX@Z
void ULockAssociationLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) ULockAssociationLinkDataObject();
}
