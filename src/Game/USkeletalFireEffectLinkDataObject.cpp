// Game/USkeletalFireEffectLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10E55E78
{
public:
    Class_10E55E78();
    ~Class_10E55E78();

    virtual void Virtual0();

    char Unknown04[0x4C];
};

// A script string member: built by its own constructor, destroyed by ~FString.
class Class_10AF8A50 : public FString
{
public:
    Class_10AF8A50();
};

class USkeletalFireEffectLinkDataObject : public Class_10E55E78
{
public:
    USkeletalFireEffectLinkDataObject();

    Class_10AF8A50 m_parentBone;
};

// FUNCTION: 0x109A0E60 ??0USkeletalFireEffectLinkDataObject@@QAE@XZ
USkeletalFireEffectLinkDataObject::USkeletalFireEffectLinkDataObject()
{
}
