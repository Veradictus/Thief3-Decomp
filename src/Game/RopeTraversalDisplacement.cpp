// Game/RopeTraversalDisplacement.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10E7E898.h"
#include "Game/Struct_10B48890.h"
#include "Game/Struct_10B1DD70_Param.h"
#include "Game/Class_1096D780.h"

FVector FUN_10b1de50(Struct_10B1DD70_Param* A);

class Class_10B49640_Anchor
{
public:
    char Unknown00[0x2c];
    FVector Location;
};

class Class_10B49640_Player
{
public:
    char Unknown00[0x2c];
    FVector Location;
    FRotator Rotation;
    char Unknown44[0x324 - 0x44];
    Class_10B49640_Anchor* Anchor;
    char Unknown328[0x404 - 0x328];
    int Unknown404;
};

class Class_10B49640_Wrapper
{
public:
    virtual void Virtual0(); virtual void Virtual1(); virtual void Virtual2(); virtual void Virtual3();
    virtual void Virtual4(); virtual void Virtual5(); virtual void Virtual6(); virtual void Virtual7();
    virtual void Virtual8(); virtual void Virtual9(); virtual void Virtual10(); virtual void Virtual11();
    virtual void Virtual12(); virtual void Virtual13(); virtual void Virtual14(); virtual void Virtual15();
    virtual void Virtual16(); virtual void Virtual17(); virtual void Virtual18(); virtual void Virtual19();
    virtual void Virtual20(); virtual void Virtual21(); virtual void Virtual22(); virtual void Virtual23();
    virtual void Virtual24(); virtual void Virtual25(); virtual void Virtual26(); virtual void Virtual27();
    virtual void Virtual28(); virtual void Virtual29(); virtual void Virtual30(); virtual void Virtual31();
    virtual void Virtual32(); virtual void Virtual33(); virtual void Virtual34(); virtual void Virtual35();
    virtual void Virtual36(); virtual void Virtual37(); virtual void Virtual38(); virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41(Class_10B49640_Player* Player, FRotator* Rotation);
};

// Partial PC field view: the generated shared base layout is inconsistent.
class cRopeMotion
{
public:
    void FUN_10b49640(int A);
    char Unknown00[0x14];
    int Unknown14;
};

// FUNCTION: 0x10B49640 ?FUN_10b49640@cRopeMotion@@QAEXH@Z
void cRopeMotion::FUN_10b49640(int A)
{
    Class_10B49640_Player* Player = (Class_10B49640_Player*)A;
    Struct_10B48890* Body = ((Class_10E7E898*)this)->FUN_10b3af40((Struct_10B3AF40_Param*)Player);
    FVector Saved = *(FVector*)&Body->Unknown14;
    FVector Direction = FUN_10b1de50((Struct_10B1DD70_Param*)Player);
    FVector Point = Direction * -1.0f * 20.0f + Player->Anchor->Location;
    Point.Z = Player->Location.Z;
    FVector Delta = Point - Player->Location;
    FVector NewLocation = Saved + Delta;
    if (Body->FUN_10b83ee0((Struct_10B4C2C0*)&NewLocation, 0))
    {
        *(FVector*)&Body->Unknown14 = Saved;
        FRotator Rotation = Player->Rotation;
        Player->Unknown404 -= Unknown14;
        Rotation.Yaw -= Unknown14;
        ((Class_10B49640_Wrapper*)((Class_1096D780*)Player)->Get())->Virtual41(Player, &Rotation);
    }
    else
        *(FVector*)&Body->Unknown14 = NewLocation;
}
