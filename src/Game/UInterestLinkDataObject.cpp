// Game/UInterestLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UInterestLinkDataObject
{
public:
    UInterestLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1790 ?InternalConstructor@UInterestLinkDataObject@@SAXPAX@Z
void UInterestLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UInterestLinkDataObject();
}
