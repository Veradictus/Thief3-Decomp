// Game/UHitSpangLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UHitSpangLinkDataObject
{
public:
    UHitSpangLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1780 ?InternalConstructor@UHitSpangLinkDataObject@@SAXPAX@Z
void UHitSpangLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UHitSpangLinkDataObject();
}
