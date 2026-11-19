// Game/AnimationPointHeight.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10BB67F0.h"
#include "Game/Class_10D38640.h"
#include "Game/Struct_10C05A80.h"

class Class_10BB48E0;

Class_10BB48E0* FUN_10bb5660();

void FUN_10c05660(Struct_10C05A80*, Struct_10D38640*);

class Class_10C299C0_Unknown04
{
public:
    void* FUN_10dbd520();
};

class cMotionControllerAnim
{
public:
    virtual void OpaqueSlot0() = 0;
    virtual void OpaqueSlot1() = 0;
    virtual void OpaqueSlot2() = 0;
    virtual void OpaqueSlot3() = 0;
    virtual void OpaqueSlot4() = 0;
    virtual void OpaqueSlot5() = 0;
    virtual void OpaqueSlot6() = 0;
    virtual void OpaqueSlot7() = 0;
    virtual void OpaqueSlot8() = 0;
    virtual void OpaqueSlot9() = 0;
    virtual void OpaqueSlot10() = 0;
    virtual void OpaqueSlot11() = 0;
    virtual void OpaqueSlot12() = 0;
    virtual void OpaqueSlot13() = 0;
    virtual void OpaqueSlot14() = 0;
    virtual void OpaqueSlot15() = 0;
    virtual void OpaqueSlot16() = 0;
    virtual void OpaqueSlot17() = 0;
    virtual void OpaqueSlot18() = 0;
    virtual void OpaqueSlot19() = 0;
    virtual void OpaqueSlot20() = 0;
    virtual void OpaqueSlot21() = 0;
    virtual void OpaqueSlot22() = 0;
    virtual void OpaqueSlot23() = 0;
    virtual void OpaqueSlot24() = 0;
    virtual void OpaqueSlot25() = 0;
    virtual void OpaqueSlot26() = 0;
    virtual void OpaqueSlot27() = 0;
    virtual void OpaqueSlot28() = 0;
    virtual void OpaqueSlot29() = 0;
    virtual void OpaqueSlot30() = 0;
    virtual void OpaqueSlot31() = 0;
    virtual void OpaqueSlot32() = 0;
    virtual void OpaqueSlot33() = 0;
    virtual Class_10C299C0_Unknown04* BorrowController() = 0;
    bool FUN_10c2f0a0(FVector* Point, float* OutZ);
    int Unknown04;
    Class_10BAA3C0* Owner;
    char Unknown0C[0xC4];
    Class_10D38640* Previous;
    Class_10D38640* Current;
};

// FUNCTION: 0x10C2F0A0 ?FUN_10c2f0a0@cMotionControllerAnim@@QAE_NPAVFVector@@PAM@Z
bool cMotionControllerAnim::FUN_10c2f0a0(FVector* Point, float* OutZ)
{
    if (Current && ((Class_10BB67F0*)FUN_10bb5660())->FUN_10bb4590((int)Current, (int)Point, 0) == true)
    {
        Struct_10C05A80 First;
        FUN_10c05660(&First, Current->FUN_10d38640());
        *OutZ = First.Unknown08;
        return true;
    }
    Class_10D38640* Found = (Class_10D38640*)((Class_10BB67F0*)FUN_10bb5660())->FUN_10bb6810(
        (int)BorrowController()->FUN_10dbd520(), (Class_10EC0808*)Current, (int)Point, 0, Owner);
    if (!Found)
        return false;
    if (Found != Current)
        Previous = Current;
    Current = Found;
    Struct_10C05A80 Second;
    FUN_10c05660(&Second, Current->FUN_10d38640());
    *OutZ = Second.Unknown08;
    return true;
}
