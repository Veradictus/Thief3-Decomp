// Game/NearestLinkedActor.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "T3Game/T3GameClasses.h"
#include "Game/cIntArray.h"
#include <math.h>

class Class_10E6CE28
{
public:
    int GetUnknown08();
};

class cUObjectLinkManager
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(int Source, int Target, int Flavor, cIntArray* Out);
};

cUObjectLinkManager* GetUObjectLinkManager();

class Class_10B06220
{
public:
    int FUN_10ad3df0(int Key, int* DataAddressOut, int OwnerOutAddress, int UnusedFourth);
};

extern int DAT_10f34954;

extern unsigned int DAT_10f34958;

struct ActorPositionView
{
    char Unknown00[0x2C];
    FVector Position;
};

struct Struct_10AA3520
{
    char Unknown00[8];
    ActorPositionView* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

inline float VectorLength(const FVector& Value)
{
    return sqrtf(Value.X * Value.X + Value.Y * Value.Y + Value.Z * Value.Z);
}

class LinkedActorSelection
{
public:
    AActor* FindNearest(int Source);
};

// FUNCTION: 0x10ACF770 ?FindNearest@LinkedActorSelection@@QAEPAVAActor@@H@Z
AActor* LinkedActorSelection::FindNearest(int Source)
{
    cIntArray Links;
    GetUObjectLinkManager()->Virtual4(Source, 0, 0x281B9D0, &Links);
    int BestIndex = -1;
    float BestDistance = 999999.0f;
    for (int I = 0; I < Links.Count; I++)
    {
        AActor* Actor = Cast<AActor>((UObject*)((Class_10E6CE28*)Links.Data[I])->GetUnknown08());
        if (Actor)
        {
            if (!(DAT_10f34958 & 1))
            {
                DAT_10f34958 |= 1;
                DAT_10f34954 = 0;
            }
            if (((Class_10B06220*)Actor)->FUN_10ad3df0(0x80056A, &DAT_10f34954, 0, 1))
            {
                float Distance = VectorLength(((ActorPositionView*)Actor)->Position - DAT_10f35dec->Unknown08->Position);
                if (Distance < BestDistance)
                {
                    BestDistance = Distance;
                    BestIndex = I;
                }
            }
        }
    }
    if (BestIndex == -1)
        return 0;
    return (AActor*)((Class_10E6CE28*)Links.Data[BestIndex])->GetUnknown08();
}
