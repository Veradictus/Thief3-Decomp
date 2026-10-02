// Game/UFrobLinkDataObject_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UFrobLinkDataObject
{
public:
    UFrobLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A16E0 ?InternalConstructor@UFrobLinkDataObject@@SAXPAX@Z
void UFrobLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UFrobLinkDataObject();
}
