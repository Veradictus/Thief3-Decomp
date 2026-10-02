// Game/Unsorted_10A75810.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class AActor : public UObject
{
public:
    BYTE Unknown2C[0x4C];           // 0x2C
    BITFIELD bDeleteMe:1;           // 0x78
};

class Object_10A75810_B
{
public:
    int Unknown00;
    int Unknown04;
};

class Object_10A75810_P
{
public:
    int Unknown00;
};

class Object_10A75810_C
{
public:
    int Unknown00;
    Object_10A75810_P* Unknown04;
};

class Class_10E6BBE8
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
    virtual void FUN_10a75810(AActor* A, Object_10A75810_B* B, Object_10A75810_C* C);
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15(AActor* A);
    virtual void FUN_10a757e0(AActor* A);
};

class UParticleEmitter;

class USpriteEmitter
{
    DECLARE_CLASS(USpriteEmitter, UParticleEmitter, 0x0, Engine)
};

// FUNCTION: 0x10A75810 ?FUN_10a75810@Class_10E6BBE8@@UAEXPAVAActor@@PAVObject_10A75810_B@@PAVObject_10A75810_C@@@Z
void Class_10E6BBE8::FUN_10a75810(AActor* A, Object_10A75810_B* B, Object_10A75810_C* C)
{
    if (B->Unknown04 == 0x80028A)
    {
        Object_10A75810_P* P = C->Unknown04;
        FUN_10a757e0(A);
        if (!A->bDeleteMe && !(A->ObjectFlags & 0x800000) && P && P->Unknown00)
            Virtual15(A);
    }
}

// FUNCTION: 0x10A75860 ??$Cast@VUSpriteEmitter@@@@YAPAVUSpriteEmitter@@PAVUObject@@@Z
template USpriteEmitter* Cast<USpriteEmitter>(UObject* Src);
