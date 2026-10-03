// Game/Unsorted_10A46300.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10A46300
{
public:
    Class_10A46300* FUN_10a46300(const Class_10A46300& Other);

    INT Unknown00;
    FString Unknown04;
    FString Unknown10;
    BYTE Unknown1C;
    BITFIELD Unknown20 : 1;
    BYTE Unknown24;
    BITFIELD Unknown28 : 1;
    INT Unknown2C;
};

// FUNCTION: 0x10A46300 ?FUN_10a46300@Class_10A46300@@QAEPAV1@ABV1@@Z
Class_10A46300* Class_10A46300::FUN_10a46300(const Class_10A46300& Other)
{
    Unknown00 = Other.Unknown00;
    Unknown04 = Other.Unknown04;
    Unknown10 = Other.Unknown10;
    Unknown1C = Other.Unknown1C;
    Unknown20 = Other.Unknown20;
    Unknown24 = Other.Unknown24;
    Unknown28 = Other.Unknown28;
    Unknown2C = Other.Unknown2C;
    return this;
}
