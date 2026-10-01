// Game/UWeaponModLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UWeaponModLinkDataObject
{
public:
    UWeaponModLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1920 ?InternalConstructor@UWeaponModLinkDataObject@@SAXPAX@Z
void UWeaponModLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UWeaponModLinkDataObject();
}
