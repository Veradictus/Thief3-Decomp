// Game/GridCandidateSelection.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <math.h>
#include "Core/Core.h"
#include "Game/Class_10C06540.h"
#include "Game/GridCandidateArray.h"

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

template<class T> class cGridPointerArray
{
public:
    cGridPointerArray() : Count(0), CapacityBytes(0), Data(0) {}
    void SetCount(int NewCount);
    void Append(T* Item)
    {
        int Index = Count;
        SetCount(Index + 1);
        Data[Index] = Item;
    }
    T* Get(int Index)
    {
        return Index >= 0 && Index < Count ? Data[Index] : 0;
    }

    int Count;
    int CapacityBytes;
    T** Data;
};

class Class_10C06940
{
public:
    void FUN_10c06b60();
    void FUN_10c067d0(FVector* Minimum, FVector* Maximum);
    Class_10C06540* FUN_10c06d30(const FVector& Position, int* RowOut, int* ColumnOut);
    cGridCandidateArray* GetCell(int Row, int Column)
    {
        if (Row < 0 || Row >= Rows.Count)
            return 0;
        return Rows.Data[Row]->Get(Column);
    }
    int Unknown00;
    int Count;
    int CapacityBytes;
    Class_10C06540** Data;
    int Unknown10;
    Class_10C06540* LastCandidate;
    cGridPointerArray<cGridPointerArray<cGridCandidateArray> > Rows;
    FVector* BoundsMinimum;
    FVector* BoundsMaximum;
};

float FUN_10bcc290();

// FUNCTION: 0x10C06D30 ?FUN_10c06d30@Class_10C06940@@QAEPAVClass_10C06540@@ABVFVector@@PAH1@Z
Class_10C06540* Class_10C06940::FUN_10c06d30(const FVector& Position, int* RowOut, int* ColumnOut)
{
    int Row;
    int Column;
    Class_10C06540* Best;
    {
        FVector Minimum;
        FVector Maximum;
        FUN_10c067d0(&Minimum, &Maximum);
        float DeltaX = Position.X - Minimum.X;
        float DeltaY = Position.Y - Minimum.Y;
        Row = (int)(DeltaX / FUN_10bcc290());
        Column = (int)(DeltaY / FUN_10bcc290());
        Best = 0;
        if (LastCandidate && LastCandidate->FUN_10afcf40() == Row &&
            LastCandidate->FUN_10dbd520() == Column &&
            LastCandidate->FUN_10c06540().Unknown08 < Position.Z + 96.0f)
            Best = LastCandidate;
    }
    if (!Best)
    {
        FUN_10c06b60();
        cGridCandidateArray* Cell = GetCell(Row, Column);
        if (!Cell || Cell->Count == 0)
            return 0;
        {
            for (int i = 0; i < Cell->Count; ++i)
            {
                Class_10C06540* Candidate = Cell->Data[i];
                if (Candidate->FUN_10c06540().Unknown08 > Position.Z + 96.0f)
                    continue;
                if (!Best)
                    Best = Candidate;
                else
                {
                    float CandidateDelta;
                    float BestDelta;
                    if (fabs(CandidateDelta = Position.Z - Candidate->FUN_10c06540().Unknown08) <
                        fabs(BestDelta = Position.Z - Best->FUN_10c06540().Unknown08))
                    {
                        if (CandidateDelta >= 0.0f)
                            Best = Candidate;
                    }
                    else if (CandidateDelta > 0.0f && BestDelta < 0.0f)
                        Best = Candidate;
                }
            }
        }
        if (!Best)
            return 0;
    }
    Best->FUN_10c06560(Position, RowOut, ColumnOut);
    LastCandidate = Best;
    return Best;
}
