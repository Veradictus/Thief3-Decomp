// Game/ActorInteractionEvent.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "T3Game/T3GameClasses.h"

class InteractionObject;

class Class_10E6C390;

class InteractionController
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
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void Virtual56();
    virtual void Virtual57();
    virtual void Virtual58();
    virtual void Virtual59();
    virtual void Virtual60();
    virtual void Virtual61();
    virtual void Virtual62();
    virtual void Virtual63();
    virtual void Virtual64();
    virtual void Virtual65();
    virtual void Virtual66();
    virtual void Virtual67();
    virtual void Virtual68();
    virtual void Virtual69();
    virtual void Virtual70();
    virtual void Virtual71();
    virtual void Virtual72();
    virtual void Virtual73();
    virtual void Virtual74();
    virtual void Virtual75();
    virtual void Virtual76();
    virtual void Virtual77();
    virtual void Virtual78();
    virtual void Virtual79();
    virtual void Virtual80();
    virtual void Virtual81();
    virtual void Virtual82();
    virtual void Virtual83();
    virtual void Virtual84();
    virtual void Virtual85();
    virtual void Virtual86();
    virtual void Virtual87();
    virtual void Virtual88();
    virtual void Virtual89();
    virtual void Virtual90();
    virtual void Virtual91();
    virtual void Virtual92();
    virtual void Virtual93();
    virtual void Virtual94();
    virtual void Virtual95();
    virtual void Virtual96();
    virtual bool CanSelect(InteractionObject* Object);
    virtual void Virtual98();
    virtual void Virtual99();
    virtual void Virtual100();
    virtual void Virtual101();
    virtual void Virtual102();
    virtual void Virtual103();
    virtual void Virtual104();
    virtual void CancelSelection();
};

struct PawnControllerView
{
    char Unknown00[0xC0];
    InteractionController* Controller;
};

class InteractionObject
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
    virtual unsigned int Flags();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual AActor* Owner();
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

Class_10E6C390* FUN_10a86080();

struct Struct_10AA3520
{
    char Unknown00[0xBC];
    InteractionManager* UnknownBC;
};

extern Struct_10AA3520* DAT_10f35dec;

class ActorInteractionRegistry
{
public:
    void OnActorEvent(int Event, UObject* Source, int Arg3, int Arg4);
    int Unknown00;
    int Count;
    int CapacityBytes;
    InteractionObject** Data;
};

// FUNCTION: 0x10A13300 ?OnActorEvent@ActorInteractionRegistry@@QAEXHPAVUObject@@HH@Z
void ActorInteractionRegistry::OnActorEvent(int Event, UObject* Source, int Arg3, int Arg4)
{
    if (Event == 16)
    {
        for (int I = 0; I < Count; I++)
        {
            if (Data[I]->Flags() & 16)
            {
                InteractionObject* Object = Data[I];
                AActor* Actor = Cast<AActor>(Source);
                if (Object->Owner() == Actor)
                {
                    APawn* Pawn = Cast<APawn>(Source);
                    if (Pawn && !((PawnControllerView*)Pawn)->Controller->CanSelect(Data[I]))
                        ((PawnControllerView*)Pawn)->Controller->CancelSelection();
                    else if (!DAT_10f35dec->UnknownBC->IsActive())
                    {
                        InteractionObject*& Slot = Data[I];
                        if (!DAT_10f35dec->UnknownBC->CheckObject(Slot, FUN_10a86080()))
                            FUN_10a86080()->SelectObject(Data[I]);
                    }
                }
            }
        }
    }
}
