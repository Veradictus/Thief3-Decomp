// Game/RopeClimbUpdate.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10991FF0.h"
#include "Game/Class_10A18E80.h"
#include "Game/Class_10D9B090.h"
#include "Game/Class_10AA82D0.h"
#include "Game/Class_10B39700.h"
#include "Game/Struct_10B7C170.h"
#include "Game/GState.h"

class Object_10A18FC0;

Object_10A18FC0* FUN_10a18fc0();

Class_10D9B090* FUN_10d9dcb0();

extern float DAT_10eafbdc;

// Native table 0x10E7E610: this method is slot 1; slot 4 is the state result.
// The two point addresses preserve the existing five-argument query binding.
class Class_10E7E610
{
public:
    virtual void Virtual0();
    virtual void FUN_10b49520(int Player);
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
};

// FUNCTION: 0x10B49520 ?FUN_10b49520@Class_10E7E610@@UAEXH@Z
void Class_10E7E610::FUN_10b49520(int Player)
{
    if (((Class_10A18E80*)FUN_10a18fc0())->FUN_10a18e80(0) > DAT_10eafbdc)
    {
        Class_10991FF0* Pawn = (Class_10991FF0*)Player;
        float Height = Pawn->FUN_10991ff0();
        FVector Start(Pawn->Unknown2C.X, Pawn->Unknown2C.Y, Pawn->Unknown2C.Z + Height);
        FVector End(Start.X, Start.Y, Start.Z + 32.0f);
        Struct_10B7C170 Hit;
        Hit.Unknown00.X = 0.0f;
        Hit.Unknown00.Y = 0.0f;
        Hit.Unknown00.Z = 0.0f;
        Hit.Unknown0C.X = 0.0f;
        Hit.Unknown0C.Y = 0.0f;
        Hit.Unknown0C.Z = 0.0f;
        Hit.Unknown18 = 0.0f;
        Hit.Unknown1C = 0.0f;
        Hit.Unknown20 = -1;
        Hit.Unknown24 = -1;
        if ((unsigned char)FUN_10d9dcb0()->FUN_10d9d640((int)&Start, (int)&End, 15, &Hit, 0))
        {
            ((Class_10B39700*)((Class_10AA82D0*)this)->GetLinkedObject())->FUN_10b39700();
            Virtual4();
            return;
        }
    }
    if (!((GState*)this)->ApplyAnimMotion(Player))
        ((Class_10B39700*)((Class_10AA82D0*)this)->GetLinkedObject())->FUN_10b39700();
    Virtual4();
}
