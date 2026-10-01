// Game/UMovementModeLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UMovementModeLinkDataObject
{
public:
    UMovementModeLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A17D0 ?InternalConstructor@UMovementModeLinkDataObject@@SAXPAX@Z
void UMovementModeLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UMovementModeLinkDataObject();
}
