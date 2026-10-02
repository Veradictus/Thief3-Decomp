// Game/Unsorted_10BAA420.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class AAIController;

class AAIPawnController
{
    DECLARE_CLASS(AAIPawnController, AAIController, 0x0, AICore)
};

class Class_10BC9D40
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3();
};

class Class_10B9CAC0
{
public:
    Class_10BC9D40* FUN_10b9cac0();
};

class Class_10BAA8A0
{
public:
    bool FUN_10baa8a0();

    Class_10B9CAC0* FUN_10baa750();
};

class Class_10E98C8C
{
public:
    ~Class_10E98C8C();

    virtual void FUN_10c162e0(int p1);

    int Unknown04;
};

struct Struct_10BAA8F0
{
    int Count;
    int Unknown04;
    Class_10E98C8C** Items;
};

// FUNCTION: 0x10BAA420 ??$Cast@VAAIPawnController@@@@YAPAVAAIPawnController@@PAVUObject@@@Z
template AAIPawnController* Cast<AAIPawnController>(UObject* Src);

// FUNCTION: 0x10BAA8A0 ?FUN_10baa8a0@Class_10BAA8A0@@QAE_NXZ
bool Class_10BAA8A0::FUN_10baa8a0()
{
    if (FUN_10baa750() && FUN_10baa750()->FUN_10b9cac0())
        return FUN_10baa750()->FUN_10b9cac0()->Virtual3() == 5;
    return false;
}

// FUNCTION: 0x10BAA8F0 ?FUN_10baa8f0@@YAXPAUStruct_10BAA8F0@@@Z
void FUN_10baa8f0(Struct_10BAA8F0* Array)
{
    for (int i = 0; i < Array->Count; i++)
        delete Array->Items[i];
    Array->Count = 0;
}
