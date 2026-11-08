// Game/GridCandidateCache.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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
    int Unknown14;
    cGridPointerArray<cGridPointerArray<cGridCandidateArray> > Rows;
};

// FUNCTION: 0x10C06B60 ?FUN_10c06b60@Class_10C06940@@QAEXXZ
void Class_10C06940::FUN_10c06b60()
{
    if (Rows.Count > 0)
        return;
    int MaxColumn = 0;
    int MaxRow = 0;
    for (int i = 0; i < Count; ++i)
    {
        Class_10C06540* Candidate = Data[i];
        if (Candidate->FUN_10afcf40() > MaxRow)
            MaxRow = Candidate->FUN_10afcf40();
        if (Candidate->FUN_10dbd520() > MaxColumn)
            MaxColumn = Candidate->FUN_10dbd520();
    }
    for (int Row = 0; Row <= MaxRow; ++Row)
    {
        GetAllocator()->Virtual8(0, 0);
        int Tag = 0;
        cGridPointerArray<cGridCandidateArray>* Cells =
            new(Tag, 0, 0, 0, 0) cGridPointerArray<cGridCandidateArray>;
        GetAllocator()->Virtual9();
        for (int Column = 0; Column <= MaxColumn; ++Column)
        {
            GetAllocator()->Virtual8(0, 0);
            int CellTag = 0;
            cGridCandidateArray* Cell = new(CellTag, 0, 0, 0, 0) cGridCandidateArray;
            Cells->Append(Cell);
            GetAllocator()->Virtual9();
        }
        Rows.Append(Cells);
    }
    for (int j = 0; j < Count; ++j)
    {
        Class_10C06540* Candidate = Data[j];
        int Column = Candidate->FUN_10dbd520();
        int Row = Candidate->FUN_10afcf40();
        GetCell(Row, Column)->Append(Candidate);
    }
}
