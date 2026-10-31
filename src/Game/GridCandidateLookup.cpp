// Game/GridCandidateLookup.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10C06540.h"
#include "Game/GridCandidateArray.h"

void* __cdecl operator new(unsigned int, const int&, int, int, int, int);

void __cdecl operator delete(void*);

class Class_10C06940
{
public:
    Class_10C06540* FUN_10c06940(int Column, int Row, float Height);

    int Unknown00;
    int Count;
    int CapacityBytes;
    Class_10C06540** Data;
};

// FUNCTION: 0x10C06940 ?FUN_10c06940@Class_10C06940@@QAEPAVClass_10C06540@@HHM@Z
Class_10C06540* Class_10C06940::FUN_10c06940(int Column, int Row, float Height)
{
    cGridCandidateArray* Matches = 0;
    Class_10C06540* First = 0;
    for (int i = 0; i < Count; ++i)
    {
        Class_10C06540* Candidate = Data[i];
        if (Candidate->FUN_10afcf40() == Column && Candidate->FUN_10dbd520() == Row)
        {
            if (!First)
                First = Candidate;
            else if (!Matches)
            {
                GetAllocator()->Virtual8(0, 0);
                int Tag = 0;
                Matches = new (Tag, 0, 0, 0, 0) cGridCandidateArray;
                GetAllocator()->Virtual9();
                Matches->Append(First);
            }
            if (Matches)
                Matches->Append(Candidate);
        }
    }
    if (!Matches)
    {
        if (!First)
            return 0;
    }
    else
    {
        First = 0;
        for (int i = 0; i < Matches->Count; ++i)
        {
            Class_10C06540* Candidate = Matches->Data[i];
            if (!First)
                First = Candidate;
            else if (Candidate->FUN_10c06540().Unknown08 > Height &&
                     Candidate->FUN_10c06540().Unknown08 < First->FUN_10c06540().Unknown08)
                First = Candidate;
        }
        delete Matches;
    }
    return First;
}
