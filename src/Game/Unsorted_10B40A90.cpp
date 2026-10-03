// Game/Unsorted_10B40A90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10B42280_Source
{
    char Unknown00[0x2C];
    FVector Unknown2C;
};

struct Struct_10B42280
{
    Struct_10B42280_Source* Unknown00;
    FVector Unknown04[200];
    int Unknown964;
    int Unknown968;
    int Unknown96C;
};

// FUNCTION: 0x10B42280 ?FUN_10b42280@@YGXPAUStruct_10B42280@@@Z
void __stdcall FUN_10b42280(Struct_10B42280* A)
{
    A->Unknown964 = 1;
    A->Unknown96C++;
    if (A->Unknown96C == 200)
        A->Unknown96C = 0;
    if (A->Unknown968 == A->Unknown96C)
    {
        A->Unknown968++;
        if (A->Unknown968 == 200)
            A->Unknown968 = 0;
    }
    A->Unknown04[A->Unknown96C] = A->Unknown00->Unknown2C;
}
