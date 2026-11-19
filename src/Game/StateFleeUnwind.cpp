// Game/StateFleeUnwind.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cString.h"
#include "Game/cStateStack.h"
#include "Game/Struct_10BB0B90.h"
#include "Game/Struct_10BB0B90_Unknown118.h"

Struct_10BB0B90* FUN_10bb0b90(int Context);

class Class_10E8C7F4 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10bb2010(int A, int Context, int C);
};

// FUNCTION: 0x10BB2010 ?FUN_10bb2010@Class_10E8C7F4@@UAEHHHH@Z
int Class_10E8C7F4::FUN_10bb2010(int A, int Context, int C)
{
    cString State("STATE_FLEE");
    Struct_10BB0B90* Controller = FUN_10bb0b90(Context);
    cStateStack* Stack = 0;
    if (Controller && Controller->Unknown118)
        Stack = (cStateStack*)Controller->Unknown118->Unknown08;
    int Result;
    if (!Stack)
        Result = 0;
    else {
        Stack->FUN_10b9ed70((int)&State);
        Result = 1;
    }
    return Result;
}
