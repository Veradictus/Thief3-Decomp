// Game/UPuddleConnectorLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UPuddleConnectorLinkDataObject
{
public:
    UPuddleConnectorLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1820 ?InternalConstructor@UPuddleConnectorLinkDataObject@@SAXPAX@Z
void UPuddleConnectorLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UPuddleConnectorLinkDataObject();
}
