// Game/AnimationCacheSelection.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10BAA580.h"

class Class_109BBBA0
{
public:
    virtual void OpaqueMeshSlot0();
    virtual void OpaqueMeshSlot1();
    virtual void OpaqueMeshSlot2();
    virtual void OpaqueMeshSlot3();
    virtual void OpaqueMeshSlot4();
    virtual void OpaqueMeshSlot5();
    virtual void OpaqueMeshSlot6();
    virtual void OpaqueMeshSlot7();
    virtual void OpaqueMeshSlot8();
    virtual void OpaqueMeshSlot9();
    virtual void OpaqueMeshSlot10();
    virtual void OpaqueMeshSlot11();
    virtual void OpaqueMeshSlot12();
    virtual void OpaqueMeshSlot13();
    virtual void OpaqueMeshSlot14();
    virtual void OpaqueMeshSlot15();
    virtual void OpaqueMeshSlot16();
    virtual void OpaqueMeshSlot17();
    virtual void OpaqueMeshSlot18();
    virtual void OpaqueMeshSlot19();
    virtual void OpaqueMeshSlot20();
    virtual void OpaqueMeshSlot21();
    virtual void OpaqueMeshSlot22();
    virtual void OpaqueMeshSlot23();
    virtual void OpaqueMeshSlot24();
    virtual void OpaqueMeshSlot25();
    virtual void OpaqueMeshSlot26();
    virtual void OpaqueMeshSlot27();
    virtual void OpaqueMeshSlot28();
    virtual void OpaqueMeshSlot29();
    virtual void OpaqueMeshSlot30();
    virtual void OpaqueMeshSlot31();
    virtual void OpaqueMeshSlot32();
    virtual void OpaqueMeshSlot33();
    virtual void OpaqueMeshSlot34();
    virtual void OpaqueMeshSlot35();
    virtual void OpaqueMeshSlot36();
    virtual void OpaqueMeshSlot37();
    virtual void OpaqueMeshSlot38();
    virtual void OpaqueMeshSlot39();
    virtual void OpaqueMeshSlot40();
    virtual void OpaqueMeshSlot41();
    virtual void OpaqueMeshSlot42();
    virtual void OpaqueMeshSlot43();
    virtual void OpaqueMeshSlot44();
    virtual void OpaqueMeshSlot45();
    virtual void OpaqueMeshSlot46();
    virtual void OpaqueMeshSlot47();
    virtual FName Virtual48(FName* Clip);
};

class cMotionControllerAnim
{
public:
    virtual void OpaqueControllerSlot0();
    virtual void OpaqueControllerSlot1();
    virtual void OpaqueControllerSlot2();
    virtual void OpaqueControllerSlot3();
    virtual void OpaqueControllerSlot4();
    virtual void OpaqueControllerSlot5();
    virtual void OpaqueControllerSlot6();
    virtual void OpaqueControllerSlot7();
    virtual void OpaqueControllerSlot8();
    virtual void OpaqueControllerSlot9();
    virtual void OpaqueControllerSlot10();
    virtual void OpaqueControllerSlot11();
    virtual void OpaqueControllerSlot12();
    virtual void OpaqueControllerSlot13();
    virtual void OpaqueControllerSlot14();
    virtual void OpaqueControllerSlot15();
    virtual FName* SelectClip(int Index, int Kind, bool Flag);
    virtual void OpaqueControllerSlot17();
    virtual void OpaqueControllerSlot18();
    virtual void OpaqueControllerSlot19();
    virtual void OpaqueControllerSlot20();
    virtual void OpaqueControllerSlot21();
    virtual void OpaqueControllerSlot22();
    virtual void OpaqueControllerSlot23();
    virtual void OpaqueControllerSlot24();
    virtual void OpaqueControllerSlot25();
    virtual void OpaqueControllerSlot26();
    virtual void OpaqueControllerSlot27();
    virtual void OpaqueControllerSlot28();
    virtual void OpaqueControllerSlot29();
    virtual void OpaqueControllerSlot30();
    virtual void OpaqueControllerSlot31();
    virtual void OpaqueControllerSlot32();
    virtual void OpaqueControllerSlot33();
    virtual void OpaqueControllerSlot34();
    virtual void OpaqueControllerSlot35();
    virtual void OpaqueControllerSlot36();
    virtual void OpaqueControllerSlot37();
    virtual void OpaqueControllerSlot38();
    virtual void OpaqueControllerSlot39();
    virtual void OpaqueControllerSlot40();
    virtual void OpaqueControllerSlot41();
    virtual void OpaqueControllerSlot42();
    virtual void OpaqueControllerSlot43();
    virtual void OpaqueControllerSlot44();
    virtual void OpaqueControllerSlot45();
    virtual void OpaqueControllerSlot46();
    virtual void OpaqueControllerSlot47();
    virtual int CurrentKind();
    virtual void OpaqueControllerSlot49();
    virtual void OpaqueControllerSlot50();
    virtual void OpaqueControllerSlot51();
    virtual void OpaqueControllerSlot52();
    virtual void OpaqueControllerSlot53();
    virtual void OpaqueControllerSlot54();
    virtual void OpaqueControllerSlot55();
    virtual void OpaqueControllerSlot56();
    virtual void OpaqueControllerSlot57();
    virtual void OpaqueControllerSlot58();
    virtual void OpaqueControllerSlot59();
    virtual void FUN_10c2f8d0(int Index, int A, int B, int C);
    int Unknown04;
    Class_10BAA580* Controller;
    char Unknown0C[0x10C];
    int CachedIndex;
    int CachedA;
    int CachedB;
    int CachedC;
    int CachedMode;
    unsigned char Pending;
    char Pad12D[3];
    FName* CachedClip;
    FName CachedName;
};

// FUNCTION: 0x10C2F8D0 ?FUN_10c2f8d0@cMotionControllerAnim@@UAEXHHHH@Z
void cMotionControllerAnim::FUN_10c2f8d0(int Index, int A, int B, int C)
{
    Class_109BBBA0* Mesh = (Class_109BBBA0*)Controller->FUN_10baa580();
    if (Mesh)
    {
        CachedClip = SelectClip(Index, CurrentKind(), false);
        if (CachedClip)
        {
            CachedName = Mesh->Virtual48(CachedClip);
            CachedMode = 8;
            CachedA = A;
            CachedB = B;
            CachedIndex = Index;
            CachedC = C;
            Pending = 0;
        }
    }
}
