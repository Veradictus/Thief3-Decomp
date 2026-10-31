// Game/AIStateEventDispatch.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Existing canonical call interfaces; only observed fields/prefixes are used.
struct Struct_10B98E00;

struct Struct_10BC4240_Param;

class Class_10BFF460
{
public:
    void* FUN_10bff2a0();
};

class Class_10BBB410
{
public:
    Class_10BFF460* GetCurrent();
};

class Class_10BE9D40;

class Class_10E939E0;

class State_Patrol;

class Class_10E935F0;

class Class_10E933B8;

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
    virtual Class_10BE9D40* FUN_10b993a0(Struct_10B98E00* A, int B, int C, int D);
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
    virtual Class_10E939E0* FUN_10b99d90(Struct_10B98E00* A);
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

class Class_10E8BE68
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
    virtual void FUN_10bc45d0(int Event);
    void FUN_10bc4240(Struct_10BC4240_Param* Param, bool Force);
    Struct_10B98E00* m_Context;
    Class_10E4CCD0* m_Factory;
};

// FUNCTION: 0x10BC45D0 ?FUN_10bc45d0@Class_10E8BE68@@UAEXH@Z
void Class_10E8BE68::FUN_10bc45d0(int Event)
{
    Struct_10BC4240_Param* Request;
    switch (Event)
    {
    case 22:
        Request = (Struct_10BC4240_Param*)m_Factory->FUN_10b99ce0(m_Context);
        break;
    case 23:
        Request = (Struct_10BC4240_Param*)m_Factory->FUN_10b99d90(m_Context);
        break;
    case 28:
        Request = (Struct_10BC4240_Param*)m_Factory->CreateSearchLookState((int)m_Context);
        break;
    case 25:
        Request = (Struct_10BC4240_Param*)m_Factory->FUN_10b97e10((int)m_Context);
        break;
    case 26:
        Request = (Struct_10BC4240_Param*)m_Factory->FUN_10b97ea0((int)m_Context);
        break;
    case 8:
        Request = (Struct_10BC4240_Param*)m_Factory->FUN_10b993a0(m_Context,
            ((Class_10BBB410*)m_Context)->GetCurrent() ?
                (int)((Class_10BBB410*)m_Context)->GetCurrent()->FUN_10bff2a0() : 0, 0, 0);
        break;
    case 51:
        Request = (Struct_10BC4240_Param*)m_Factory->FUN_10b98170(m_Context);
        break;
    default:
        return;
    }
    if (Request)
        FUN_10bc4240(Request, false);
}
