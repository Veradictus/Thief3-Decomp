// Game/Class_109B2A40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_109B2A40
{
public:
    FName FUN_109b2a40(FName* Name);
};

// FUNCTION: 0x109B2A40 ?FUN_109b2a40@Class_109B2A40@@QAE?AVFName@@PAV2@@Z
FName Class_109B2A40::FUN_109b2a40(FName* Name)
{
    if (Name)
        return *Name;
    return NAME_None;
}
