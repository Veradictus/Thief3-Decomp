// Game/MotionAnimationPlayback.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10BAA580.h"
#include "Game/Class_109BBBA0.h"
#include "Game/Class_1098E330.h"
#include "Game/Class_10BAA6F0.h"
#include "Game/Class_10BB9FC0.h"
#include "Game/Struct_10FF66BC.h"

extern float DAT_10f069d8;

extern float DAT_10eafbdc;

extern Struct_10FF66BC DAT_10ff66bc[];

class cMotionControllerAnim
{
public:
    virtual void OpaqueSlot0();
    virtual void OpaqueSlot1();
    virtual void OpaqueSlot2();
    virtual void OpaqueSlot3();
    virtual void OpaqueSlot4();
    virtual void OpaqueSlot5();
    virtual void OpaqueSlot6();
    virtual void OpaqueSlot7();
    virtual void OpaqueSlot8();
    virtual void OpaqueSlot9();
    virtual void OpaqueSlot10();
    virtual void OpaqueSlot11();
    virtual void OpaqueSlot12();
    virtual bool FUN_10c2eec0(int Index, const FName& Tag, unsigned char Loop, unsigned char Notify);
    virtual void OpaqueSlot14();
    virtual void OpaqueSlot15();
    virtual FName* SelectClip(int Index, int Kind, bool Flag);
    virtual void OpaqueSlot17();
    virtual void OpaqueSlot18();
    virtual void OpaqueSlot19();
    virtual void OpaqueSlot20();
    virtual void OpaqueSlot21();
    virtual void OpaqueSlot22();
    virtual void OpaqueSlot23();
    virtual void OpaqueSlot24();
    virtual void OpaqueSlot25();
    virtual void OpaqueSlot26();
    virtual void OpaqueSlot27();
    virtual void OpaqueSlot28();
    virtual void OpaqueSlot29();
    virtual void OpaqueSlot30();
    virtual void OpaqueSlot31();
    virtual void OpaqueSlot32();
    virtual void OpaqueSlot33();
    virtual void OpaqueSlot34();
    virtual void OpaqueSlot35();
    virtual void OpaqueSlot36();
    virtual void OpaqueSlot37();
    virtual void OpaqueSlot38();
    virtual void OpaqueSlot39();
    virtual void OpaqueSlot40();
    virtual void OpaqueSlot41();
    virtual void OpaqueSlot42();
    virtual void OpaqueSlot43();
    virtual void OpaqueSlot44();
    virtual void OpaqueSlot45();
    virtual void OpaqueSlot46();
    virtual void OpaqueSlot47();
    virtual int CurrentKind();
    int Opaque04;
    Class_10BAA580* Controller;
    Class_1098E330* Actor;
    char Opaque10[0x8E];
    unsigned char Started;
};

// FUNCTION: 0x10C2EEC0 ?FUN_10c2eec0@cMotionControllerAnim@@UAE_NHABVFName@@EE@Z
bool cMotionControllerAnim::FUN_10c2eec0(int Index, const FName& Tag, unsigned char Loop, unsigned char Notify)
{
    FName* Clip = SelectClip(Index, CurrentKind(), false);
    if (!Clip)
        return false;
    float Rate = DAT_10f069d8 * *(const float*)DAT_10ff66bc[Index].Unknown04;
    if (Actor)
    {
        float Scale = 0.0f;
        Actor->GetPropertyValue(0x100310, (int*)&Scale);
        if (Scale >= DAT_10eafbdc)
            Rate *= Scale;
    }
    Class_109BBBA0* ChannelMesh = (Class_109BBBA0*)Controller->FUN_10baa580();
    ChannelMesh->Virtual60(4);
    Class_109BBBA0* PlayMesh = (Class_109BBBA0*)Controller->FUN_10baa580();
    PlayMesh->Virtual44((int)Clip, Rate, 0, Loop, -1.0f, -1, 0, 1);
    Class_109BBBA0* BlendMesh = (Class_109BBBA0*)Controller->FUN_10baa580();
    BlendMesh->FUN_109b6580(1.0f, 0, 0, Tag);
    if (Notify)
        ((Class_10BB9FC0*)((Class_10BAA6F0*)Controller)->FUN_10baa6f0())->FUN_10bb9fc0();
    Started = 1;
    return true;
}
