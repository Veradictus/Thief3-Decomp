// Game/FactionContextActor.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10C16300.h"

// Same receiver returned by the existing 10BAA6F0 context getter.
// The native thunk passes its embedded handle at offset0x2a0 to GetActor.
class Class_10BAA6F0_Result
{
public:
    AActor* FUN_10bb80d0();
    char Unknown00[0x2A0];
    Class_10C16300 ActorHandle;
};

// FUNCTION: 0x10BB80D0 ?FUN_10bb80d0@Class_10BAA6F0_Result@@QAEPAVAActor@@XZ
AActor* Class_10BAA6F0_Result::FUN_10bb80d0()
{
    return ActorHandle.GetActor();
}
