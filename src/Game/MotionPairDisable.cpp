// Game/MotionPairDisable.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10B7AC90.h"

// Native 10B47090 and adjacent inverse10B47060 visit exactly these two receivers.
class Class_10B47090
{
public:
    void FUN_10b47090();
    char Pad00[8];
    Class_10B7AC90* Unknown08[2];
};

// FUNCTION: 0x10B47090 ?FUN_10b47090@Class_10B47090@@QAEXXZ
void Class_10B47090::FUN_10b47090()
{
    for (int i = 0; i < 2; i++)
        Unknown08[i]->FUN_10b7ac90(false);
}
