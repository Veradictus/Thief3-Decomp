// Game/UWaypointInterpolationLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UWaypointInterpolationLinkDataObject
{
public:
    UWaypointInterpolationLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1910 ?InternalConstructor@UWaypointInterpolationLinkDataObject@@SAXPAX@Z
void UWaypointInterpolationLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UWaypointInterpolationLinkDataObject();
}
