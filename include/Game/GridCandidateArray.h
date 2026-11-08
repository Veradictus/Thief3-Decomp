#ifndef GAME_GRIDCANDIDATEARRAY_H
#define GAME_GRIDCANDIDATEARRAY_H

#include "Game/Class_10905A90_Member.h"

class Class_10C06540;
Class_10905A90_Member* GetAllocator();

// A non-owning list of grid candidates. The shared native resize routine
// manages four-byte slots; destruction releases the buffer, never candidates.
class cGridCandidateArray
{
public:
    cGridCandidateArray() : Count(0), CapacityBytes(0), Data(0) {}

    void Append(Class_10C06540* Item)
    {
        int Index = Count;
        SetCount(Index + 1);
        Data[Index] = Item;
    }

    void SetCount(int NewCount)
    {
        int Capacity = !Data ? 0 : CapacityBytes / sizeof(Class_10C06540*);
        GetAllocator()->Virtual8(0, 0);
        if (NewCount > Capacity)
        {
            int NewCapacity = NewCount;
            if (Capacity)
                NewCapacity = (NewCount & ~15) + 16;
            Data = (Class_10C06540**)GetAllocator()->Virtual3(
                Data, NewCapacity * sizeof(Class_10C06540*), 0, 0, 0, 0);
            CapacityBytes = NewCapacity * sizeof(Class_10C06540*);
        }
        else if (NewCount <= Capacity - 16)
        {
            if (NewCount == 0)
            {
                GetAllocator()->Virtual5(Data);
                Data = 0;
                CapacityBytes = 0;
            }
            else
            {
                int NewCapacity = (NewCount & ~15) + 16;
                Data = (Class_10C06540**)GetAllocator()->Virtual3(
                    Data, NewCapacity * sizeof(Class_10C06540*), 0, 0, 0, 0);
                CapacityBytes = NewCapacity * sizeof(Class_10C06540*);
            }
        }
        GetAllocator()->Virtual9();
        Count = NewCount;
    }

    ~cGridCandidateArray()
    {
        SetCount(0);
        if (CapacityBytes)
        {
            GetAllocator()->Virtual5(Data);
            Data = 0;
            CapacityBytes = 0;
        }
    }

    int Count;
    int CapacityBytes;
    Class_10C06540** Data;
};

#endif
