// Game/UTriggerScriptLinkDataObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class UTriggerScriptLinkDataObject : public Class_10E55E78
{
public:
    UTriggerScriptLinkDataObject();

    Class_10AF8A50 LinkName;
};

// FUNCTION: 0x109A1200 ??0UTriggerScriptLinkDataObject@@QAE@XZ
UTriggerScriptLinkDataObject::UTriggerScriptLinkDataObject()
{
}
