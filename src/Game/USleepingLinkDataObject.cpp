// Game/USleepingLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class USleepingLinkDataObject
{
public:
    USleepingLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1880 ?InternalConstructor@USleepingLinkDataObject@@SAXPAX@Z
void USleepingLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) USleepingLinkDataObject();
}
