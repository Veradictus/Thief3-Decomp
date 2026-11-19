// Game/WaterEventHandling.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cWaterManager.h"
#include "Game/Class_1098E330.h"
#include "Game/Class_10971570.h"
#include "Game/Class_10AB9D40.h"

struct WaterEventPayload561
{
    int Unknown00;
    Class_1098E330* Volume;
};

struct WaterActorState561
{
    char Pad00[8];
    int Mode;
};

struct WaterActorView561
{
    char Pad00[0x78];
    unsigned char Flags;
    char Pad79[0x37];
    WaterActorState561* State;
};

struct WaterVolumeView561
{
    char Pad00[0x134];
    float SurfaceZ;
};

// FUNCTION: 0x10AB9D90 ?HandleEvent@cWaterManager@@UAEXHHHH@Z
void cWaterManager::HandleEvent(int Type, int A, int B, int C)
{
    if (!Unknown28)
    {
        if (Type == 90)
            Unknown28 = 1;
        return;
    }
    switch (Type)
    {
    case 40:
        {
            Class_1098E330* Volume = ((WaterEventPayload561*)B)->Volume;
            int Enabled = 0;
            Volume->GetPropertyValue(0x800465, &Enabled);
            if (!Enabled)
                return;
            WaterActorView561* Actor = (WaterActorView561*)A;
            WaterActorState561* State = Actor->State;
            if (!(Actor->Flags & 4) && (!State ||
                (State->Mode != 1 && State->Mode != 3)))
                return;
            unsigned char Kind = 0;
            if (!((Class_10971570*)Volume)->FUN_10971570(0x20000AF, &Kind))
                return;
            switch (Kind)
            {
            case 7:
                FUN_10ab9850(A, 1, 0.0f, Volume);
                break;
            case 6:
                {
                    float Depth = 0.0f;
                    Volume->GetPropertyValue(0x401007EE, (int*)&Depth);
                    FUN_10ab9850(A, 0, Depth + ((WaterVolumeView561*)Volume)->SurfaceZ, Volume);
                    break;
                }
            }
            break;
        }
    case 41:
        {
            Class_1098E330* Volume = ((WaterEventPayload561*)B)->Volume;
            int Enabled = 0;
            Volume->GetPropertyValue(0x800465, &Enabled);
            if (!Enabled)
                return;
            WaterActorView561* Actor = (WaterActorView561*)A;
            WaterActorState561* State = Actor->State;
            if (!(Actor->Flags & 4) && (!State ||
                (State->Mode != 1 && State->Mode != 3)))
                return;
            unsigned char Kind = 0;
            if (((Class_10971570*)Volume)->FUN_10971570(0x20000AF, &Kind) && Kind >= 6 && Kind <= 7)
                FUN_10ab9240(A, 0, Volume);
            break;
        }
    case 6:
        FUN_10ab8c70(A, B, C);
        break;
    case 42:
        ((Class_10AB9D40*)this)->HandleFootstep(A, (Struct_10AB9D40*)B, C);
        break;
    case 43:
    case 90:
        break;
    default:
        return;
    }
}
