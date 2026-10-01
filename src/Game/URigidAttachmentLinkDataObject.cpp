// Game/URigidAttachmentLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class URigidAttachmentLinkDataObject
{
public:
    URigidAttachmentLinkDataObject();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109A1600 ?InternalConstructor@URigidAttachmentLinkDataObject@@SAXPAX@Z
void URigidAttachmentLinkDataObject::InternalConstructor(void* X)
{
    new ((EInternal*)X) URigidAttachmentLinkDataObject();
}
