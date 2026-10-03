// Game/Unsorted_10B7C170.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10B7C330
{
public:
    void FUN_10b7c330(const Class_10B7C330& Other);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
};

struct Struct_10B7C030_Param;

struct Struct_10B7C170
{
    FVector Unknown00;
    FVector Unknown0C;
    float Unknown18;
    float Unknown1C;
    int Unknown20;
    int Unknown24;
};

class Class_10D9B090
{
public:
    int FUN_10d9d640(int A, int B, int C, Struct_10B7C170* Out, int D);
};

Class_10D9B090* FUN_10d9dcb0();

class Class_10E4B180
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
    virtual void FUN_10b7c6a0(int A);
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void FUN_10b7c030(Struct_10B7C030_Param* A);
    virtual int FUN_10b7c170(int A, int B, FVector* Out);
};

// FUNCTION: 0x10B7C170 ?FUN_10b7c170@Class_10E4B180@@UAEHHHPAVFVector@@@Z
int Class_10E4B180::FUN_10b7c170(int A, int B, FVector* Out)
{
    Struct_10B7C170 Hit;
    Hit.Unknown00.X = 0.0f;
    Hit.Unknown00.Y = 0.0f;
    Hit.Unknown00.Z = 0.0f;
    Hit.Unknown0C.X = 0.0f;
    Hit.Unknown0C.Y = 0.0f;
    Hit.Unknown0C.Z = 0.0f;
    Hit.Unknown18 = 0.0f;
    Hit.Unknown1C = 0.0f;
    Hit.Unknown20 = -1;
    Hit.Unknown24 = -1;
    int Result = FUN_10d9dcb0()->FUN_10d9d640(A, B, 3, &Hit, 0);
    *Out = Hit.Unknown00;
    return Result;
}

// FUNCTION: 0x10B7C330 ?FUN_10b7c330@Class_10B7C330@@QAEXABV1@@Z
void Class_10B7C330::FUN_10b7c330(const Class_10B7C330& Other)
{
    Unknown00 = Other.Unknown00;
    Unknown04 = Other.Unknown04;
    Unknown08 = Other.Unknown08;
    Unknown0C = Other.Unknown0C;
    Unknown10 = Other.Unknown10;
    Unknown14 = Other.Unknown14;
    Unknown18 = Other.Unknown18;
    Unknown1C = Other.Unknown1C;
    Unknown20 = Other.Unknown20;
    Unknown24 = Other.Unknown24;
    Unknown28 = Other.Unknown28;
    Unknown2C = Other.Unknown2C;
}
