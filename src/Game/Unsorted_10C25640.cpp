// Game/Unsorted_10C25640.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10C25770
{
public:
    int FUN_10c25770(int* Value);

    int Unknown00;
    char Unknown04[4];
    int* Unknown08;
};

class Class_10C064D0
{
public:
    FVector FUN_10c064d0(int A, int B);
};

class Class_10C25EB0
{
public:
    FVector FUN_10c25eb0();

    Class_10C064D0* Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10C25770 ?FUN_10c25770@Class_10C25770@@QAEHPAH@Z
int Class_10C25770::FUN_10c25770(int* Value)
{
    for (int i = 0; i < Unknown00; i++)
    {
        if (Unknown08[i] == *Value)
            return i;
    }
    return -1;
}

// FUNCTION: 0x10C25EB0 ?FUN_10c25eb0@Class_10C25EB0@@QAE?AVFVector@@XZ
FVector Class_10C25EB0::FUN_10c25eb0()
{
    if (!Unknown00)
        return FVector(0.0f, 0.0f, 0.0f);
    return Unknown00->FUN_10c064d0(Unknown04, Unknown08);
}
