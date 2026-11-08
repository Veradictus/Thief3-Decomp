// Game/LockPickStageComplete.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cString.h"
#include "Game/Class_10A3C550.h"
#include "Game/Class_10B39530.h"
#include "Game/Class_10B54760.h"
#include "Game/Class_10AD0350.h"

class Class_10B3E820_Unknown08
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual bool Virtual8();
};

class Class_10B3E820_Unknown5C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    char Unknown04[4];
    Class_10B3E820_Unknown08* Unknown08;
};

class Class_10C56E40
{
public:
    Class_10C56E40() : Unknown00(0) {}
    Class_10C56E40(Class_10B3E820_Unknown5C* P) : Unknown00(P)
    {
        if (Unknown00)
            Unknown00->Virtual1();
    }
    Class_10C56E40(const Class_10C56E40& Other) : Unknown00(Other.Unknown00)
    {
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10C56E40()
    {
        if (Unknown00)
            Unknown00->Virtual2();
    }
    bool operator!=(const Class_10C56E40& Other) const
    {
        return Unknown00 != Other.Unknown00;
    }
    Class_10B3E820_Unknown08* operator->() const
    {
        return Unknown00->Unknown08;
    }
    Class_10C56E40& operator=(const Class_10C56E40& Other)
    {
        Class_10B3E820_Unknown5C* Old = Unknown00;
        Unknown00 = Other.Unknown00;
        if (Unknown00)
            Unknown00->Virtual1();
        if (Old)
            Old->Virtual2();
        return *this;
    }
    Class_10B3E820_Unknown5C* Unknown00;
};

T3_CHECK_SIZE(Class_10C56E40, 4);

class Class_10ACA6A0
{
public:
    Class_10C56E40 FUN_10aca6a0(int Kind, int Flags);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0xFC];
    Class_10AD0350* UnknownFC;
    char Unknown100[0x20];
    Class_10ACA6A0* Unknown120;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

struct Struct_10AA3520
{
    char Unknown00[0x94];
    Class_10A3C550* Unknown94;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_1098E3D0;

class Class_10B3F830_Arg
{
public:
    char Unknown00[0x458];
    Class_1098E3D0* Unknown458;
};

class Class_10B39870;

class Class_10AA82D0
{
public:
    virtual void Virtual0();
    Class_10B39870* GetLinkedObject();
    char Unknown04[4];
    Class_10B39870* Unknown08;
};

class cLockPickController : public Class_10AA82D0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    void ClearSlots(int Slot);
    void FUN_10b3f280(Class_10B3F830_Arg* A);
    void FUN_10b3f070(Class_10B3F830_Arg* A);
    void FUN_10b3f670(Class_10B3F830_Arg* A);
    char Unknown0C[0x30];
    int Unknown3C;
    int Unknown40;
    char Unknown44[8];
    bool m_ResetPending;
    char Unknown4D;
    bool Unknown4E;
    bool Unknown4F;
    char Unknown50[0xC];
    Class_10C56E40 m_Slots[4];
};

class Class_10B542D0;

Class_10B542D0* GetLockPickWindowManager();

// FUNCTION: 0x10B3F670 ?FUN_10b3f670@cLockPickController@@QAEXPAVClass_10B3F830_Arg@@@Z
void cLockPickController::FUN_10b3f670(Class_10B3F830_Arg* A)
{
    ClearSlots(4);
    if (m_Slots[3] != 0 && m_Slots[3]->Virtual8())
        ClearSlots(3);
    if (!m_Slots[3].Unknown00)
        m_Slots[3] = DAT_10f3a3d8->Unknown120->FUN_10aca6a0(6, 0);
    FUN_10b3f280(A);
    DAT_10f3a3d8->UnknownFC->FUN_10ad0350((int)A->Unknown458);
    FUN_10b3f070(A);
    ((Class_10B54760*)GetLockPickWindowManager())->AdvanceToNext();
    m_ResetPending = false;
    ((Class_10B39530*)GetLinkedObject())->Play(0xBE, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    ((Class_10B39530*)GetLinkedObject())->Play(0xBF, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    ((Class_10B39530*)GetLinkedObject())->Play(0xB7, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    Unknown3C = 4;
    Unknown40 = 4;
    DAT_10f35dec->Unknown94->Start(cString("LPCompleteStage"));
    Unknown4E = false;
    Unknown4F = false;
}
