// Game/UFireEffectLinkDataObject_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UFireEffectLinkDataObject
{
public:
    UFireEffectLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A16C0 ?InternalConstructor@UFireEffectLinkDataObject@@SAXPAX@Z
void UFireEffectLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UFireEffectLinkDataObject();
}
