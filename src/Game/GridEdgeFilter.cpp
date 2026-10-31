// Game/GridEdgeFilter.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <math.h>

class FVector
{
public:
    FVector() {}
    FVector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector& V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    float operator|(const FVector& V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    void NormalizeXY()
    {
        Z = 0.0f;
        float Square = X * X + Y * Y;
        if (Square >= 0.00000001)
        {
            float Scale = (float)(1.0 / sqrt((double)Square));
            X = (float)(X * Scale);
            Y = (float)(Y * Scale);
            Z = (float)(Z * Scale);
        }
    }
    float X, Y, Z;
};

struct cGridEdgeRecord
{
    FVector Start;
    FVector End;
    FVector Normal;
};

class Class_10BAEC80
{
public:
    void FUN_10a211e0(int Count);
    void Append(const cGridEdgeRecord& Record)
    {
        int Index = Count;
        FUN_10a211e0(Count + 1);
        Data[Index] = Record;
    }
    int Count;
    int CapacityBytes;
    cGridEdgeRecord* Data;
};

struct cGridEdgeArray
{
    int Count;
    int Unknown04;
    cGridEdgeRecord* Data;
};

struct cGridRegionRecord
{
    char Unknown00[0x14];
    cGridEdgeArray Edges;
    int Type;
};

class Class_10C25010
{
public:
    void FUN_10c22ee0(Class_10BAEC80* OutEdges, const cGridRegionRecord* Region, const FVector* Position);
};

// FUNCTION: 0x10C22EE0 ?FUN_10c22ee0@Class_10C25010@@QAEXPAVClass_10BAEC80@@PBUcGridRegionRecord@@PBVFVector@@@Z
void Class_10C25010::FUN_10c22ee0(Class_10BAEC80* OutEdges, const cGridRegionRecord* Region, const FVector* Position)
{
    FVector Direction;
    for (int i = 0; i < Region->Edges.Count; ++i)
    {
        Direction = Region->Edges.Data[i].Start - *Position;
        Direction.NormalizeXY();
        if ((Direction | Region->Edges.Data[i].Normal) > -0.01f)
            continue;
        Direction = Region->Edges.Data[i].End - *Position;
        Direction.NormalizeXY();
        if ((Direction | Region->Edges.Data[i].Normal) > -0.01f)
            continue;
        OutEdges->Append(Region->Edges.Data[i]);
        OutEdges->Data[OutEdges->Count - 1].Start.Z = Position->Z;
        OutEdges->Data[OutEdges->Count - 1].End.Z = Position->Z;
    }
}
