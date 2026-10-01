// Game/UElevatorLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UElevatorLinkDataObject
{
public:
    UElevatorLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A16A0 ?InternalConstructor@UElevatorLinkDataObject@@SAXPAX@Z
void UElevatorLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UElevatorLinkDataObject();
}
