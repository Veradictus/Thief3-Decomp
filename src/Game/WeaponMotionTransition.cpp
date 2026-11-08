// Game/WeaponMotionTransition.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "T3Player/T3PlayerClasses.h"
#include "Game/Class_10B1D660.h"
#include "Game/Struct_10AA3520.h"
#include "Game/Class_10B39530.h"

extern float DAT_10eafbdc;

class Class_10B4D010_Param;

class Class_10B39870;

// Accepted Unsorted_10C16250_2.cpp controller view: result method is slot4.
class cLockPickController
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
};

class Class_10B228E0
{
public:
    int CurrentStateId() { return Unknown90->Virtual4(); }
    char Pad00[0x90];
    cLockPickController* Unknown90;
};

class Class_10B21560
{
public:
    unsigned char FUN_10b21560();
};

class Class_10B398C0
{
public:
    void FUN_10b398c0(int Index);
};

class Class_10B39750
{
public:
    float QueryHandlerValue(int Id);
};

// Accepted Class_10E7E970.cpp linked state view; animation08 is at offset08.
class Class_10AA82D0
{
public:
    virtual void Virtual0();
    Class_10B39870* GetLinkedObject();
    char Pad04[4];
    int Unknown08;
    int m_LinkedObject;
};

class Class_10E7E9B8 : public Class_10AA82D0
{
public:
    void FUN_10b4c840(Class_10B4D010_Param* P);
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10B4C840 ?FUN_10b4c840@Class_10E7E9B8@@QAEXPAVClass_10B4D010_Param@@@Z
void Class_10E7E9B8::FUN_10b4c840(Class_10B4D010_Param* P)
{
    Unknown08 = 0x101;
    AGarrett* Garrett = (AGarrett*)P;
    bool Idle = DAT_10f35dec->GetUnknown0C()->Unknown2C4.FUN_10b1d1b0()->CurrentStateId() == 0
        && Garrett->InputSpeed == GSP_IDLE;
    int Extra = 0x101;
    switch (Garrett->WeaponStanceTypeHolding)
    {
    case 10:
        if (Idle && ((Class_10B21560*)P)->FUN_10b21560())
            Extra = Garrett->isCrouching ? 0xC6 : 0xC2;
        Unknown08 = Garrett->isCrouching ? 0xC4 : 0xC0;
        if (((Class_10B39750*)GetLinkedObject())->QueryHandlerValue(0x61) < DAT_10eafbdc)
            ((Class_10B39530*)GetLinkedObject())->Play(0x61, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
        break;
    case 3:
        if (Idle && ((Class_10B21560*)P)->FUN_10b21560())
            Extra = Garrett->isCrouching ? 0x69 : 0x65;
        Unknown08 = Garrett->isCrouching ? 0x67 : 0x63;
        break;
    case 2:
        if (Idle && ((Class_10B21560*)P)->FUN_10b21560())
            Extra = Garrett->isCrouching ? 0x76 : 0x72;
        Unknown08 = Garrett->isCrouching ? 0x74 : 0x70;
        if (((Class_10B39750*)GetLinkedObject())->QueryHandlerValue(0x60) < DAT_10eafbdc)
            ((Class_10B39530*)GetLinkedObject())->Play(0x60, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
        break;
    }
    if (Unknown08 != 0x101)
        ((Class_10B39530*)GetLinkedObject())->Play(Unknown08, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    if (Extra != 0x101)
    {
        ((Class_10B39530*)GetLinkedObject())->Play(Extra, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
        ((Class_10B398C0*)GetLinkedObject())->FUN_10b398c0(0);
    }
}
