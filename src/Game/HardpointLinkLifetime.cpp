// Game/HardpointLinkLifetime.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

// FUNCTION: 0x1099FF10 ??1UHardpointLinkDataObject@@UAE@XZ
UHardpointLinkDataObject::~UHardpointLinkDataObject()
{
    ConditionalDestroy();
}
