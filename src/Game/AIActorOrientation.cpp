// Game/AIActorOrientation.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Engine/EngineClasses.h"
#include "Game/Class_1096D780.h"
#include "Game/Class_10BAC050.h"
#include "Game/Class_10BABED0.h"

class Class_10BAA6B0_Param;

class AAIPawn : public APawn
{
    DECLARE_CLASS(AAIPawn, APawn, 0x0, AICore)
public:
    void FUN_10bc2ff0();
};

Class_10BABED0* FUN_10baa6b0(Class_10BAA6B0_Param* Pawn);

class Class_10BC2FF0_Node
{
public:
    char Unknown00[0xC0];
    AActor* UnknownC0;
    char UnknownC4[8];
    Class_10BC2FF0_Node* UnknownCC;
};

class Level
{
public:
    char Unknown00[0x2C8];
    Class_10BC2FF0_Node* Unknown2C8;
};

class Class_10974340
{
public:
    Level* FUN_10974340();
    char Pad00[1];
};

class Class_10B056C0
{
public:
    void FUN_10b056c0(FRotator& Out);
};

class Class_10BC2FF0_Wrapper
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
    virtual void Virtual41(AAIPawn* Pawn, FRotator* Rotation);
};

// FUNCTION: 0x10BC2FF0 ?FUN_10bc2ff0@AAIPawn@@QAEXXZ
void AAIPawn::FUN_10bc2ff0()
{
    Class_10BABED0* Context = FUN_10baa6b0((Class_10BAA6B0_Param*)this);
    if (Context && ((Class_1096D780*)this)->Get())
    {
        AActor* Best = 0;
        ::Level* World = ((Class_10974340*)((Class_1096D780*)this)->Get())->FUN_10974340();
        float BestDistance = 1000000.0f;
        for (Class_10BC2FF0_Node* Item = World->Unknown2C8; Item; Item = Item->UnknownCC)
        {
            if (Item->UnknownC0 && Item->UnknownC0->Virtual34() == 0 &&
                ((Class_10BAC050*)Context)->FUN_10baac90((int)Item->UnknownC0) == 0)
            {
                FVector Delta = Item->UnknownC0->Location - Location;
                float Distance = Delta.X * Delta.X + Delta.Y * Delta.Y + Delta.Z * Delta.Z;
                if (Distance < BestDistance)
                {
                    BestDistance = Distance;
                    Best = Item->UnknownC0;
                }
            }
        }
        if (Best)
        {
            FVector Delta = Best->Location - Location;
            FRotator Rotation;
            ((Class_10B056C0*)&Delta)->FUN_10b056c0(Rotation);
            Rotation.Pitch = 0;
            Rotation.Roll = 0;
            ((Class_10BC2FF0_Wrapper*)((Class_1096D780*)this)->Get())->Virtual41(this, &Rotation);
        }
    }
}
