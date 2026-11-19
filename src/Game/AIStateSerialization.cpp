// Game/AIStateSerialization.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/FArchive.h"
#include "Game/cIntArray.h"
#include "Game/Class_10FF667C.h"
#include "Game/Class_10FF667C_Unknown18.h"

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

FArchive& FUN_10b052a0(FArchive& Ar, void* Value);

extern Class_10FF667C* DAT_10ff667c;

class Class_10E8BE68
{
public:
    virtual void Serialize(FArchive& Ar);
};

class Class_10E970E8
{
public:
    Class_10E970E8() : Unknown04(0) {}
    virtual void FUN_10be9800(void* Value);
    virtual void Serialize(FArchive& Ar);
    int Unknown04;
    FVector Unknown08;
    int Unknown14;
    char Unknown18;
    char Unknown19;
    char Pad1A[2];
};

T3_CHECK_SIZE(Class_10E970E8, 28);

class StateSerialization
{
public:
    virtual void Virtual0();
    void Serialize(FArchive& Ar);
    char Unknown04[0x3C];
    int Unknown40;
    int Unknown44;
    void* Unknown48;
    char Unknown4C[8];
    cIntArray Items;
    Class_10E970E8* Current;
    unsigned char Unknown64;
    unsigned char Unknown65;
    char Unknown66[2];
    int Unknown68;
    unsigned char Unknown6C;
    unsigned char Unknown6D;
    unsigned char Unknown6E;
    char Unknown6F[5];
    UObject* Unknown74;
    int Unknown78;
    int Unknown7C;
    int Unknown80;
    int Unknown84;
};

// FUNCTION: 0x10BE9F50 ?Serialize@StateSerialization@@QAEXAAVFArchive@@@Z
void StateSerialization::Serialize(FArchive& Ar)
{
    ((Class_10E8BE68*)this)->Class_10E8BE68::Serialize(Ar);
    DAT_10ff667c->Unknown18->Virtual1(Ar, &Unknown40);
    Ar.Serialize(&Unknown44, 4);
    FUN_10b052a0(Ar, &Unknown48);
    int Count = Items.Count;
    Ar.Serialize(&Count, 4);
    if (Ar.Unknown14)
        Items.SetCount(Count);
    for (int i = 0; i < Count; ++i)
    {
        if (Ar.Unknown14)
            Items.Data[i] = (int)new(0, 0, 0, 0, 0) Class_10E970E8;
        ((Class_10E970E8*)Items.Data[i])->Serialize(Ar);
    }
    if (Ar.Unknown0C >= 92)
    {
        bool Present = Current != 0;
        Ar.Serialize(&Present, 1);
        if (Present)
        {
            if (Ar.Unknown14)
                Current = new(0, 0, 0, 0, 0) Class_10E970E8;
            Current->Serialize(Ar);
        }
    }
    else
    {
        bool Present = Current != 0;
        Ar.Serialize(&Present, 1);
        if (Present)
        {
            int Index = 0;
            if (Ar.Unknown14)
            {
                Ar.Serialize(&Index, 4);
                Current = (Class_10E970E8*)Items.Data[Index];
            }
            else
            {
                for (int j = 0; j < Items.Count; ++j)
                    if (Items.Data[j] == (int)Current)
                        Index = j;
                Ar.Serialize(&Index, 4);
            }
        }
    }
    Ar.Serialize(&Unknown64, 1);
    Ar.Serialize(&Unknown65, 1);
    Ar.Serialize(&Unknown68, 4);
    Ar.Serialize(&Unknown6C, 1);
    Ar.Virtual6(&Unknown74);
    if (Ar.Unknown0C >= 45)
        Ar.Serialize(&Unknown6D, 1);
    if (Ar.Unknown0C >= 77)
    {
        Ar.Serialize(&Unknown78, 4);
        Ar.Serialize(&Unknown7C, 4);
    }
    if (Ar.Unknown0C >= 108)
        Ar.Serialize(&Unknown6E, 1);
    if (Ar.Unknown0C >= 122)
        Ar.Serialize(&Unknown84, 4);
}
