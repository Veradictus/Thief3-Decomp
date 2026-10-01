// Game/USwooshLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class USwooshLinkDataObject
{
public:
    USwooshLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A18B0 ?InternalConstructor@USwooshLinkDataObject@@SAXPAX@Z
void USwooshLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) USwooshLinkDataObject();
}
