// Game/UCollisionSpawnLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10E55E78
{
public:
    virtual void Virtual0();
};

class USpawnableHardpointLinkDataObject : public Class_10E55E78
{
public:
    USpawnableHardpointLinkDataObject();
    ~USpawnableHardpointLinkDataObject();

    char Unknown04[0x6C];
};

// A script string member: built by its own constructor, destroyed by ~FString.
class Class_10AF8A50 : public FString
{
public:
    Class_10AF8A50();
};

class UCollisionSpawnLinkDataObject : public USpawnableHardpointLinkDataObject
{
public:
    UCollisionSpawnLinkDataObject();

    unsigned int Active : 1;
    Class_10AF8A50 Tag;
};

// FUNCTION: 0x109A0390 ??0UCollisionSpawnLinkDataObject@@QAE@XZ
UCollisionSpawnLinkDataObject::UCollisionSpawnLinkDataObject()
{
}
