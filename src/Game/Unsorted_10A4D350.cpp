// Game/Unsorted_10A4D350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

// FUNCTION: 0x10A4D350 ?FUN_10a4d350@@YG?AVFString@@H@Z
FString __stdcall FUN_10a4d350(int Mode)
{
    FString Name;
    if (Mode == 1)
        Name = "Look at Actor";
    else if (Mode == 2)
        Name = "Face Path";
    else if (Mode == 3)
        Name = "Interpolation";
    else
        Name = "None";
    return Name;
}
