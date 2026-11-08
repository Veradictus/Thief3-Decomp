// Game/GridControllerConstructor.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cString.h"
#include "Game/cIntArray.h"
#include "Game/Class_10E9925C.h"

extern void* DAT_10e9925c[];

class Class_109BC840
{
public:
    int FUN_109b5860(int Key);
};

class Class_10C26980
{
public:
    Class_10C26980(int A, int B, int C, int D, float E, float F);
    void** Vtable;
    int Unknown04;
    int Unknown08;
    int RegistryId;
    cString Name;
    float Unknown14;
    float Unknown18;
    FVector Unknown1C;
    FVector Unknown28;
    unsigned char Flag34;
    unsigned char Flag35;
    cIntArray Items;
};

// FUNCTION: 0x10C26980 ??0Class_10C26980@@QAE@HHHHMM@Z
Class_10C26980::Class_10C26980(int A, int B, int C, int D, float E, float F)
    : Vtable(DAT_10e9925c), Unknown04(A), Unknown08(B), RegistryId(-1),
      Name(*(const cString*)D), Unknown14(E), Unknown18(F),
      Unknown1C(0, 0, 0), Unknown28(0, 0, 0), Flag34(0), Flag35(0)
{
    Class_10E9925C* Object = (Class_10E9925C*)this;
    if (Object->FUN_10c26490())
        RegistryId = ((Class_109BC840*)Object->FUN_10c26490())->FUN_109b5860(*(int*)C);
}
