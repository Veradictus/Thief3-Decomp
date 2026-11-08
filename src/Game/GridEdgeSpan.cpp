// Game/GridEdgeSpan.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUNCTION: 0x10C061C0 ?FUN_10c061c0@@YA_NPBVFVector@@PBUcGridEdgeArray@@@Z
bool FUN_10c061c0(const FVector* Position, const cGridEdgeArray* Edges)
{
    cGridEdgeRecord Crossings[2];
    int Found = 0;
    for (int i = 0; i < Edges->Count; ++i)
    {
        const cGridEdgeRecord& Edge = Edges->Data[i];
        if ((Position->Y > Edge.Start.Y && Position->Y < Edge.End.Y) ||
            (Position->Y < Edge.Start.Y && Position->Y > Edge.End.Y))
        {
            Crossings[Found] = Edge;
            ++Found;
            if (Found == 2)
                break;
        }
    }
    if (Found >= 2)
    {
        float FirstSlope = (Crossings[0].End.X - Crossings[0].Start.X) /
            (Crossings[0].End.Y - Crossings[0].Start.Y);
        float FirstX = Crossings[0].Start.X - FirstSlope * Crossings[0].Start.Y +
            FirstSlope * Position->Y;
        float SecondSlope = (Crossings[1].End.X - Crossings[1].Start.X) /
            (Crossings[1].End.Y - Crossings[1].Start.Y);
        float SecondX = Crossings[1].Start.X - SecondSlope * Crossings[1].Start.Y +
            SecondSlope * Position->Y;
        if ((FirstX > SecondX && Position->X < FirstX && Position->X > SecondX) ||
            (SecondX > FirstX && Position->X > FirstX && Position->X < SecondX))
            return true;
    }
    return false;
}
