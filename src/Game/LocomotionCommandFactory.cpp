// Game/LocomotionCommandFactory.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10BAA580.h"
#include "Game/Class_10905A90_Member.h"

Class_10905A90_Member* GetAllocator();

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern float DAT_10eafbdc;

class cMotionControllerAnim;

class Duration228View
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
    virtual void SetDuration(float Value);
    char Opaque04[0x44];
};

class cLocomotionCommand
{
public:
    cLocomotionCommand(void* Actor, Class_109BC840* Pawn, cMotionControllerAnim* Owner);
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
    virtual void OpaqueSlot13();
    virtual void OpaqueSlot14();
    virtual void OpaqueSlot15();
    virtual void OpaqueSlot16();
    virtual void OpaqueSlot17();
    virtual void OpaqueSlot18();
    virtual void OpaqueSlot19();
    virtual void OpaqueSlot20();
    virtual void SetPosition(const FVector& Value);
    virtual void OpaqueSlot22();
    virtual void OpaqueSlot23();
    virtual void OpaqueSlot24();
    virtual void OpaqueSlot25();
    virtual void SetMode(int Value);
    char Opaque04[0x38];
    Duration228View Duration;
};

typedef char VerifyCommand228Size[sizeof(cLocomotionCommand) == 0x84 ? 1 : -1];

class cMotionControllerAnim
{
public:
    virtual void OpaqueFactorySlot0();
    virtual void OpaqueFactorySlot1();
    virtual void OpaqueFactorySlot2();
    virtual void OpaqueFactorySlot3();
    virtual cLocomotionCommand* FUN_10c2f340(const FVector& Point, int Mode, float Time);
    int Opaque04;
    Class_10BAA580* Controller;
    void* Actor;
    int Opaque10;
    float DefaultTime;
};

// FUNCTION: 0x10C2F340 ?FUN_10c2f340@cMotionControllerAnim@@UAEPAVcLocomotionCommand@@ABVFVector@@HM@Z
cLocomotionCommand* cMotionControllerAnim::FUN_10c2f340(const FVector& Point, int Mode, float Time)
{
    GetAllocator()->Virtual8(0, 0);
    cLocomotionCommand* Command = new(0, 0, 0, 0, 0) cLocomotionCommand(Actor, Controller->FUN_10baa580(), this);
    GetAllocator()->Virtual9();
    const float SelectedTime = Time >= DAT_10eafbdc ? Time : DefaultTime;
    Command->Duration.SetDuration(SelectedTime);
    Command->SetPosition(Point);
    Command->SetMode(Mode);
    return Command;
}
