// Game/Unsorted_10A6AE00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10E6B8C8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7(int A);
    virtual void Virtual8();
    virtual void Virtual9();
    virtual int Virtual10(int A);
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void FUN_10a6b3c0(int A);
};

class AActor : public UObject
{
public:
    BYTE Unknown2C[0x4C];           // 0x2C
    BITFIELD bDeleteMe:1;           // 0x78
};

class Object_10A6AEA0_B
{
public:
    int Unknown00;
    int Unknown04;
};

class Object_10A6AEA0_P
{
public:
    int Unknown00;
};

class Object_10A6AEA0_C
{
public:
    int Unknown00;
    Object_10A6AEA0_P* Unknown04;
};

class Class_10E6B764
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7(AActor* A);
    virtual void FUN_10a6aea0(AActor* A, Object_10A6AEA0_B* B, Object_10A6AEA0_C* C);

    void FUN_10a6ae00(AActor* A, int B);
};

struct Struct_10A6B140
{
    Struct_10A6B140(int X, int Y, int Z) : Unknown00(X), Unknown04(Y), Unknown08(Z) {}

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10A6AEA0 ?FUN_10a6aea0@Class_10E6B764@@UAEXPAVAActor@@PAVObject_10A6AEA0_B@@PAVObject_10A6AEA0_C@@@Z
void Class_10E6B764::FUN_10a6aea0(AActor* A, Object_10A6AEA0_B* B, Object_10A6AEA0_C* C)
{
    if (B->Unknown04 == 0x800526)
    {
        Object_10A6AEA0_P* P = C->Unknown04;
        Virtual7(A);
        if (!A->bDeleteMe && !(A->ObjectFlags & 0x800000) && P)
            FUN_10a6ae00(A, P->Unknown00);
    }
}

// FUNCTION: 0x10A6B140 ?FUN_10a6b140@@YA?AUStruct_10A6B140@@MABU1@@Z
Struct_10A6B140 FUN_10a6b140(float Scale, const Struct_10A6B140& In)
{
    return Struct_10A6B140((int)(In.Unknown00 * Scale), (int)(In.Unknown04 * Scale), (int)(In.Unknown08 * Scale));
}

// FUNCTION: 0x10A6B3C0 ?FUN_10a6b3c0@Class_10E6B8C8@@UAEXH@Z
void Class_10E6B8C8::FUN_10a6b3c0(int A)
{
    if (Virtual10(A))
        Virtual7(A);
}
