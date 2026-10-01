// Game/UBotDominationLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UBotDominationLinkDataObject
{
public:
    UBotDominationLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1630 ?InternalConstructor@UBotDominationLinkDataObject@@SAXPAX@Z
void UBotDominationLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UBotDominationLinkDataObject();
}
