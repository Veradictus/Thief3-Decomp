// Game/Unsorted_10C3D8B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Info_10C3DD40
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E5B2C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10c3dd40(const Info_10C3DD40* In);

    char Unknown04[0x18];
    Info_10C3DD40 Unknown1C;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

FArchive& FUN_10b052a0(FArchive& Ar, void* Data);

class Class_10E9AFD0
{
public:
    virtual ~Class_10E9AFD0();

    void FUN_10c3db00(FArchive& Ar);

    char Unknown04[0x18];
};

class Class_10E9B168 : public Class_10E9AFD0
{
public:
    void FUN_10c3dc80(FArchive& Ar);

    FVector Unknown1C;
    float Unknown28;
    bool Unknown2C;
};

// FUNCTION: 0x10C3DC80 ?FUN_10c3dc80@Class_10E9B168@@QAEXAAVFArchive@@@Z
void Class_10E9B168::FUN_10c3dc80(FArchive& Ar)
{
    FUN_10c3db00(Ar);
    FUN_10b052a0(Ar, &Unknown1C);
    Ar.Serialize(&Unknown28, 4);
    Ar.Serialize(&Unknown2C, 1);
}

// FUNCTION: 0x10C3DD40 ?FUN_10c3dd40@Class_10E5B2C0@@UAEXPBUInfo_10C3DD40@@@Z
void Class_10E5B2C0::FUN_10c3dd40(const Info_10C3DD40* In)
{
    Unknown1C = *In;
}
