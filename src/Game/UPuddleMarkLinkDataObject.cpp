// Game/UPuddleMarkLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UPuddleMarkLinkDataObject
{
public:
    UPuddleMarkLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1830 ?InternalConstructor@UPuddleMarkLinkDataObject@@SAXPAX@Z
void UPuddleMarkLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UPuddleMarkLinkDataObject();
}
