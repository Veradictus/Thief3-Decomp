// Game/AIObjectCallback.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cString.h"
#include "Game/Class_10C7D570.h"
#include "Game/Class_1098E3D0.h"
#include "Game/Class_10BFF460.h"
#include "Game/Struct_10BA91E0.h"
#include "Game/Class_10BBB410.h"

class ThrowAttachment {
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
    virtual void Virtual10(UObject* Target);
};

// Structural actor interface: observed slots and position, not a complete class.
class ThrowActor {
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
    virtual ThrowAttachment* Virtual93();
    virtual void Virtual94();
    virtual void Virtual95();
    virtual void Virtual96(void* A, void* B);
    char Unknown04[0x28];
    FVector Position;
};

class ThrowEventManager {
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
    virtual void Virtual15(UObject* Target, void* Owner, int Flag);
};

struct Struct_10AA3520;

extern Struct_10AA3520* DAT_10f35dec;

struct ThrowGlobals {
    char Unknown00[0x9C];
    ThrowEventManager* Events;
};

struct ThrowOwner {
    char Unknown00[8];
    Class_10C7D570* Pawn;
};

int FUN_10a37390(UObject* Target);

void FUN_10d660b0(UObject* Target, const cString& Name, float Value);

float Distance(const Struct_10BA91E0* A, const Struct_10BA91E0* B);

// The original vtable at10E94B20 identifies this method as slot72.
class Class_10E94B20 {
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
    virtual void FUN_10bdc6d0(UObject* Target);
    ThrowOwner* Owner;
    char Unknown08[0x4D];
    bool Unknown55;
    char Unknown56[0xE];
    float Radius;
};

// FUNCTION: 0x10BDC6D0 ?FUN_10bdc6d0@Class_10E94B20@@UAEXPAVUObject@@@Z
void Class_10E94B20::FUN_10bdc6d0(UObject* Target)
{
    if (!Unknown55) {
        ThrowAttachment* Attachment = ((ThrowActor*)Owner->Pawn->FUN_10c7d570())->Virtual93();
        if (Attachment) {
            ((ThrowActor*)Owner->Pawn->FUN_10c7d570())->Virtual96(0, 0);
            Attachment->Virtual10(Target);
            cString Name(DAT_10e47660);
            FUN_10d660b0(Target, Name, 1.0f);
        }
    }
    FUN_10a37390(Target);
    void* Pawn = Owner->Pawn->FUN_10c7d570();
    ((Class_1098E3D0*)Target)->FUN_1098e3d0(0x2047B, &Pawn);
    ((ThrowGlobals*)DAT_10f35dec)->Events->Virtual15(Target, Pawn, 1);
    Class_10BFF460* Current = ((Class_10BBB410*)Owner)->GetCurrent();
    if (Current) {
        Class_10C7D570* PawnOwner = Owner->Pawn;
        if (!(Distance((const Struct_10BA91E0*)&((ThrowActor*)PawnOwner->FUN_10c7d570())->Position,
                       (const Struct_10BA91E0*)&Current->FUN_10bff360()) < Radius))
            Current->FUN_10bff360();
    }
}
