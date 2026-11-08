// Game/InteractionRegistryUpdate.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class InteractionObject;

class Class_10E6C390;

class InteractionObject
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int UpdateState(int Flag);
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual bool IsSpecial();
    virtual void Virtual11();
    virtual bool ContainsPosition(const FVector* Position);
};

class InteractionManager
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual bool CheckObject(InteractionObject* Object, Class_10E6C390* Context);
    virtual void Virtual15();
    virtual bool IsActive();
};

class Class_10E6C390
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void SelectObject(InteractionObject* Object);
};

class Class_10F352D8
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void UpdateState();
};

Class_10E6C390* FUN_10a86080();

bool HasObject(int Object);

bool FUN_10a871d0(int Object);

void FUN_10a87950(int Time);

void FUN_10a872a0(int Time);

extern Class_10F352D8* DAT_10f352d8;

struct PlayerPositionView
{
    char Unknown00[0x2C];
    FVector Position;
};

struct Struct_10AA3520
{
    char Unknown00[8];
    PlayerPositionView* Unknown08;
    char Unknown0C[0xB0];
    InteractionManager* UnknownBC;
};

extern Struct_10AA3520* DAT_10f35dec;

class InteractionUpdateRegistry
{
public:
    void Update(int Time);
    int Unknown00;
    int Unknown04;
    int Count;
    int CapacityBytes;
    InteractionObject** Data;
    char Unknown14[0x1C];
    int Unknown30;
};

// FUNCTION: 0x10A13190 ?Update@InteractionUpdateRegistry@@QAEXH@Z
void InteractionUpdateRegistry::Update(int Time)
{
    if (Unknown30)
        DAT_10f352d8->UpdateState();
    if (DAT_10f35dec && DAT_10f35dec->Unknown08)
    {
        for (int I = 0; I < Count; I++)
        {
            if (Data[I]->UpdateState(1))
            {
                if (Data[I]->IsSpecial())
                {
                    if (!HasObject((int)Data[I]) && Data[I]->ContainsPosition(&DAT_10f35dec->Unknown08->Position))
                        FUN_10a871d0((int)Data[I]);
                }
                else if (Data[I]->ContainsPosition(&DAT_10f35dec->Unknown08->Position) && !DAT_10f35dec->UnknownBC->IsActive())
                {
                    InteractionObject*& Slot = Data[I];
                    if (!DAT_10f35dec->UnknownBC->CheckObject(Slot, FUN_10a86080()))
                        FUN_10a86080()->SelectObject(Data[I]);
                }
            }
        }
        FUN_10a87950(Time);
        FUN_10a872a0(Time);
    }
}
