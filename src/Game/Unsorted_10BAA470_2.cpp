// Game/Unsorted_10BAA470_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class AAIController;

class AController;

class AAIPawnController
{
    DECLARE_CLASS(AAIPawnController, AAIController, 0x0, AICore)
};

class Class_10B9BCA0
{
public:
    char Unknown00[0x118];
};

class AAIPawn
{
public:
    char Unknown00[0xC0];
    UObject* Controller;
};

// FUNCTION: 0x10BAA660 ?FUN_10baa660@@YAPAVClass_10B9BCA0@@PAVAAIPawn@@@Z
Class_10B9BCA0* FUN_10baa660(AAIPawn* Pawn)
{
    return (Class_10B9BCA0*)Cast<AAIPawnController>(Pawn->Controller);
}
