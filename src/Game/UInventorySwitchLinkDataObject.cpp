// Game/UInventorySwitchLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UInventorySwitchLinkDataObject
{
public:
    UInventorySwitchLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10AB53B0 ?InternalConstructor@UInventorySwitchLinkDataObject@@SAXPAX@Z
void UInventorySwitchLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UInventorySwitchLinkDataObject();
}
