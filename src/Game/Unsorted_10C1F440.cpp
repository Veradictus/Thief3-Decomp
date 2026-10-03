// Game/Unsorted_10C1F440.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

FArchive& FUN_10b052a0(FArchive& Ar, void* Data);

class Class_10E991C0
{
public:
    virtual void FUN_10c1f440(FArchive& Ar);

    FVector Unknown04;
    int Unknown10;
    int Unknown14;
    int Unknown18;
};

class Class_10FF667C
{
public:
    char Unknown00[0x54];
    int Unknown54;
    int Unknown58;
    int Unknown5C;
    int Unknown60;
    int Unknown64;
    int Unknown68;
};

extern Class_10FF667C* DAT_10ff667c;

struct Struct_10C1F490
{
    int Unknown00;
};

class Class_10C1F490
{
public:
    int FUN_10c1f490(Struct_10C1F490* A);
};

// FUNCTION: 0x10C1F440 ?FUN_10c1f440@Class_10E991C0@@UAEXAAVFArchive@@@Z
void Class_10E991C0::FUN_10c1f440(FArchive& Ar)
{
    FUN_10b052a0(Ar, &Unknown04);
    Ar.Serialize(&Unknown10, 4);
    Ar.Serialize(&Unknown14, 4);
    Ar.Serialize(&Unknown18, 4);
}

// FUNCTION: 0x10C1F490 ?FUN_10c1f490@Class_10C1F490@@QAEHPAUStruct_10C1F490@@@Z
int Class_10C1F490::FUN_10c1f490(Struct_10C1F490* A)
{
    int Kind = A->Unknown00;
    if (Kind == DAT_10ff667c->Unknown54 || Kind == DAT_10ff667c->Unknown58 || Kind == DAT_10ff667c->Unknown5C || Kind == DAT_10ff667c->Unknown60 || Kind == DAT_10ff667c->Unknown64 || Kind == DAT_10ff667c->Unknown68)
        return 1;
    return 0;
}
