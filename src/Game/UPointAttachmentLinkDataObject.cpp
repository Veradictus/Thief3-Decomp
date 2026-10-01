// Game/UPointAttachmentLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UPointAttachmentLinkDataObject
{
public:
    UPointAttachmentLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A15F0 ?InternalConstructor@UPointAttachmentLinkDataObject@@SAXPAX@Z
void UPointAttachmentLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) UPointAttachmentLinkDataObject();
}
