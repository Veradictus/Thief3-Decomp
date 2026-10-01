// Game/UFragRoundLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UFragRoundLinkDataObject
{
public:
    UFragRoundLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1730 ?InternalConstructor@UFragRoundLinkDataObject@@SAXPAX@Z
void UFragRoundLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UFragRoundLinkDataObject();
}
