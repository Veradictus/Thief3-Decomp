// Game/GridRegionQuery.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct cGridEdgeRecord
{
    FVector Start;
    FVector End;
    char Unknown18[0xC];
};

struct cGridEdgeArray
{
    int Count;
    int Unknown04;
    cGridEdgeRecord* Data;
};

bool FUN_10c061c0(const FVector* Position, const cGridEdgeArray* Edges);

float DistanceSquared3D(const FVector* A, const FVector* B);

extern float DAT_10e49684;

class Class_10BB48E0
{
public:
    void* FUN_10bb67f0(const FVector* Position, int Flags, void* Owner);
};

Class_10BB48E0* FUN_10bb5660();

struct cGridRadiusContext
{
    int Unknown00;
    int Unknown04;
};

struct cGridRegionRecord
{
    int Unknown00;
    FVector Center;
    float Radius;
    cGridEdgeArray Edges;
    int Type;
};

struct cGridRegionArray
{
    int Count;
    int Unknown04;
    cGridRegionRecord* Data;
};

class cGridRegionSet
{
public:
    bool FUN_10c21340(const FVector* Position, const cGridRadiusContext* Context,
        FVector* OutCenter, float* OutRadius);

    void* Unknown00;
    char Unknown04[0x20];
    cGridRegionArray Regions;
};

// FUNCTION: 0x10C21340 ?FUN_10c21340@cGridRegionSet@@QAE_NPBVFVector@@PBUcGridRadiusContext@@PAV2@PAM@Z
bool cGridRegionSet::FUN_10c21340(const FVector* Position, const cGridRadiusContext* Context,
    FVector* OutCenter, float* OutRadius)
{
    for (int i = 0; i < Regions.Count; ++i)
    {
        switch (Regions.Data[i].Type)
        {
        case 1:
            if (FUN_10c061c0(Position, &Regions.Data[i].Edges))
            {
                *OutCenter = FVector(0.0f, 0.0f, 0.0f);
                int NumPoints = 0;
                for (int j = 0; j < Regions.Data[i].Edges.Count; ++j)
                {
                    *OutCenter += Regions.Data[i].Edges.Data[j].Start;
                    *OutCenter += Regions.Data[i].Edges.Data[j].End;
                    NumPoints += 2;
                }
                float Scale = DAT_10e49684 / NumPoints;
                OutCenter->X *= Scale;
                OutCenter->Y *= Scale;
                OutCenter->Z *= Scale;
                *OutRadius = 16.0f;
                return true;
            }
            break;
        case 0:
            {
                float Radius = Context->Unknown04 + Regions.Data[i].Radius;
                if (DistanceSquared3D(&Regions.Data[i].Center, Position) < Radius * Radius)
                {
                    *OutCenter = Regions.Data[i].Center;
                    *OutRadius = Regions.Data[i].Radius;
                    return true;
                }
            }
            break;
        }
    }
    Class_10BB48E0* Manager = FUN_10bb5660();
    if (Manager->FUN_10bb67f0(Position, 1, Unknown00) != 0)
        return false;
    return true;
}
