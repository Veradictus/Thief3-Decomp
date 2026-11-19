// Game/PatrolStateFactory.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10C7D570.h"
#include "Game/Class_10BBDB40.h"

struct Struct_10B98E00
{
    char Unknown00[8];
    Class_10C7D570* Unknown08;
};

int FUN_10becff0();

extern float DAT_10eafbdc;

// Allocation-sized PC views; constructors are external, vtables are not emitted here.
class State_Patrol
{
public:
    State_Patrol(int A, int B);
    char Unknown00[0x84];
};

class Class_10E935F0
{
public:
    Class_10E935F0(int A, int B);
    char Unknown00[0x58];
};

class Class_10E933B8
{
public:
    Class_10E933B8(int A, int B);
    char Unknown00[0x44];
};

class cCombatBase;

class cYellowAlert;

class State_Gassed;

class Class_10E92460;

class Class_10E92730;

class Class_10E928E8;

class State_PlayAction;

class State_PlayAnim;

class State_SearchLook;

class Class_10E93878;

class cSampleStats;

class cTacticWeaponHolster;

class Class_10E95288;

class State_MunchCorpse;

class Class_10E95898;

class Class_10E95AC8;

class Class_10E96EB0;

class Class_10E96FD0;

class State_PatrolLook;

struct Struct_10B98E00;

class Class_10E4CCD0
{
public:
    virtual void Virtual0();
    virtual Class_10E95288* FUN_10b98e00(Struct_10B98E00* A);
    virtual void Virtual2();
    virtual Class_10E95898* FUN_10b98f60(Struct_10B98E00* A, int B, bool C);
    virtual void Virtual4();
    virtual cYellowAlert* FUN_10b990d0(Struct_10B98E00* A);
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual State_PlayAnim* CreatePlayAnimState(Struct_10B98E00* A, int B, bool C);
    virtual void Virtual11();
    virtual void Virtual12();
    virtual State_Patrol* FUN_10b99530(Struct_10B98E00* A);
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual State_PatrolLook* CreatePatrolLookState(Struct_10B98E00* A, int B, int C, int D, int E, int F, int G);
    virtual void Virtual18();
    virtual State_Gassed* CreateGassedState(Struct_10B98E00* A, int B);
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual Class_10E93878* FUN_10b99ce0(Struct_10B98E00* A);
    virtual void Virtual24();
    virtual Class_10E935F0* FUN_10b97e10(int A);
    virtual Class_10E933B8* FUN_10b97ea0(int A);
    virtual State_SearchLook* CreateSearchLookState(int A);
    virtual void Virtual28();
    virtual void Virtual29();
    virtual cSampleStats* FUN_10b980e0(int A);
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual State_PlayAction* CreatePlayActionState(Struct_10B98E00* A, bool B, bool C);
    virtual cCombatBase* FUN_10b98170(Struct_10B98E00* A);
    virtual void Virtual36();
    virtual cTacticWeaponHolster* CreateTacticWeaponHolster(int A);
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual Class_10E928E8* FUN_10b98570(int A, int B);
    virtual void Virtual43();
    virtual void Virtual44();
    virtual Class_10E96EB0* FUN_10b99ef0(Struct_10B98E00* A, int B, int C);
    virtual Class_10E96FD0* FUN_10b99470(Struct_10B98E00* A, int B);
    virtual Class_10E92730* FUN_10b98740(int A);
    virtual Class_10E95AC8* FUN_10b987d0(int A, int B);
    virtual void Virtual49();
    virtual void Virtual50();
    virtual Class_10E95288* FUN_10b98980(Struct_10B98E00* A);
    virtual void Virtual52();
    virtual void Virtual53();
    virtual Class_10E92460* FUN_10b98aa0(int A, int B);
    virtual State_MunchCorpse* CreateMunchCorpseState(int A, int B);
};

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

// FUNCTION: 0x10B99530 ?FUN_10b99530@Class_10E4CCD0@@UAEPAVState_Patrol@@PAUStruct_10B98E00@@@Z
State_Patrol* Class_10E4CCD0::FUN_10b99530(Struct_10B98E00* A)
{
    int Id = FUN_10becff0();
    if (Id && A->Unknown08->FUN_10dbd510()->GetFloat(Id) > DAT_10eafbdc)
        return new(0, 0, 0, 0, 0) State_Patrol((int)A, (int)this);
    return 0;
}
