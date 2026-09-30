// Game/Class_109CD810.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_109CD810
{
public:
    FName FUN_109cd810(int Flag);

    char Unknown00[0xBC];
    FName UnknownBC;
};

// FUNCTION: 0x109CD810 ?FUN_109cd810@Class_109CD810@@QAE?AVFName@@H@Z
FName Class_109CD810::FUN_109cd810(int Flag)
{
    if (Flag == 0)
        return UnknownBC;
    return NAME_None;
}
