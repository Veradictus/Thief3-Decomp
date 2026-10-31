// Game/PawnModelReplacement.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "AICore/AICoreClasses.h"
#include "Game/Struct_10C37D30.h"
#include "Game/Class_1096D780.h"

class PawnModelWorld
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43();
    virtual void Virtual44(void* Model, int Flag);
    virtual void Slot45();
    virtual void* Virtual46(int ModelClass, Struct_10C37D30 Name, FVector Location, FRotator Rotation,
        int A, int B, int C, int D, int Context, int E, int F, int G, int H);
};

// Observed paired model slots; this view does not describe the complete owner.
class Class_10BBDB40
{
public:
    void FUN_10bbd370(int ModelClass, AAIPawn* Pawn);
    void FUN_10bbd460(int ModelClass, AAIPawn* Pawn);
    void FUN_10bbd550(int ModelClass, AAIPawn* Pawn);
    void FUN_10bbd640(int ModelClass, AAIPawn* Pawn);

    char Unknown00[4];
    AAISensoryModel* SensoryModel;
    AAIBehaviorModel* BehaviorModel;
    AAIMovementModel* MovementModel;
    AAICombatModel* CombatModel;
    AAIFactionModel* FactionModel;
};

// FUNCTION: 0x10BBD370 ?FUN_10bbd370@Class_10BBDB40@@QAEXHPAVAAIPawn@@@Z
void Class_10BBDB40::FUN_10bbd370(int ModelClass, AAIPawn* Pawn)
{
    if (ModelClass && Pawn && Pawn->IsA(AAIPawn::StaticClass()))
    {
        AAISensoryModel* Model = (AAISensoryModel*)((PawnModelWorld*)((Class_1096D780*)Pawn)->Get())->Virtual46(
            ModelClass, Struct_10C37D30(), Pawn->Location, Pawn->Rotation,
            0, 0, 0, 0, 0, 0, 1, 0, 0);
        if (Model)
        {
            if (SensoryModel)
            {
                ((PawnModelWorld*)((Class_1096D780*)Pawn)->Get())->Virtual44(SensoryModel, 0);
                SensoryModel = 0;
                Pawn->SensoryModel = 0;
            }
            SensoryModel = Model;
            Pawn->SensoryModel = Model;
        }
    }
}

// FUNCTION: 0x10BBD460 ?FUN_10bbd460@Class_10BBDB40@@QAEXHPAVAAIPawn@@@Z
void Class_10BBDB40::FUN_10bbd460(int ModelClass, AAIPawn* Pawn)
{
    if (ModelClass && Pawn && Pawn->IsA(AAIPawn::StaticClass()))
    {
        AAICombatModel* Model = (AAICombatModel*)((PawnModelWorld*)((Class_1096D780*)Pawn)->Get())->Virtual46(
            ModelClass, Struct_10C37D30(), Pawn->Location, Pawn->Rotation,
            0, 0, 0, 0, 0, 0, 1, 0, 0);
        if (Model)
        {
            if (CombatModel)
            {
                ((PawnModelWorld*)((Class_1096D780*)Pawn)->Get())->Virtual44(CombatModel, 0);
                CombatModel = 0;
                Pawn->CombatModel = 0;
            }
            CombatModel = Model;
            Pawn->CombatModel = Model;
        }
    }
}

// FUNCTION: 0x10BBD550 ?FUN_10bbd550@Class_10BBDB40@@QAEXHPAVAAIPawn@@@Z
void Class_10BBDB40::FUN_10bbd550(int ModelClass, AAIPawn* Pawn)
{
    if (ModelClass && Pawn && Pawn->IsA(AAIPawn::StaticClass()))
    {
        AAIBehaviorModel* Model = (AAIBehaviorModel*)((PawnModelWorld*)((Class_1096D780*)Pawn)->Get())->Virtual46(
            ModelClass, Struct_10C37D30(), Pawn->Location, Pawn->Rotation,
            0, 0, 0, 0, 0, 0, 1, 0, 0);
        if (Model)
        {
            if (BehaviorModel)
            {
                ((PawnModelWorld*)((Class_1096D780*)Pawn)->Get())->Virtual44(BehaviorModel, 0);
                BehaviorModel = 0;
                Pawn->BehaviorModel = 0;
            }
            BehaviorModel = Model;
            Pawn->BehaviorModel = Model;
        }
    }
}

// FUNCTION: 0x10BBD640 ?FUN_10bbd640@Class_10BBDB40@@QAEXHPAVAAIPawn@@@Z
void Class_10BBDB40::FUN_10bbd640(int ModelClass, AAIPawn* Pawn)
{
    if (ModelClass && Pawn && Pawn->IsA(AAIPawn::StaticClass()))
    {
        AAIFactionModel* Model = (AAIFactionModel*)((PawnModelWorld*)((Class_1096D780*)Pawn)->Get())->Virtual46(
            ModelClass, Struct_10C37D30(), Pawn->Location, Pawn->Rotation,
            0, 0, 0, 0, 0, 0, 1, 0, 0);
        if (Model)
        {
            if (FactionModel)
            {
                ((PawnModelWorld*)((Class_1096D780*)Pawn)->Get())->Virtual44(FactionModel, 0);
                FactionModel = 0;
                Pawn->FactionModel = 0;
            }
            FactionModel = Model;
            Pawn->FactionModel = Model;
        }
    }
}
