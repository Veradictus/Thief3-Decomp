// Game/AITargetWeightSelection.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10905A90_Member.h"

Class_10905A90_Member* GetAllocator();

class Class_10978090Result;

// Game/cIntArray.h copied whole, with SetCount inline as this unit compiles it
// (the header declares it out of line).
class cIntArray
{
public:
    cIntArray() : Unknown00(0), m_CapacityBytes(0), Unknown08(0) {}
    cIntArray(const cIntArray& Other)
    {
        Unknown00 = m_CapacityBytes = 0;
        Unknown08 = 0;
        CopyFrom(Other);
    }
    void SetCount(int NewCount)
    {
        int Capacity = !Unknown08 ? 0 : m_CapacityBytes / sizeof(void*);
        GetAllocator()->Virtual8(0, 0);
        if (NewCount > Capacity)
        {
            int NewCapacity = NewCount;
            if (Capacity)
                NewCapacity = (NewCount & ~15) + 16;
            Unknown08 = (int*)GetAllocator()->Virtual3(Unknown08, NewCapacity * sizeof(void*), 0, 0, 0, 0);
            m_CapacityBytes = NewCapacity * sizeof(void*);
        }
        else if (NewCount <= Capacity - 16)
        {
            if (NewCount == 0)
            {
                GetAllocator()->Virtual5(Unknown08);
                Unknown08 = 0;
                m_CapacityBytes = 0;
            }
            else
            {
                int NewCapacity = (NewCount & ~15) + 16;
                Unknown08 = (int*)GetAllocator()->Virtual3(Unknown08, NewCapacity * sizeof(void*), 0, 0, 0, 0);
                m_CapacityBytes = NewCapacity * sizeof(void*);
            }
        }
        GetAllocator()->Virtual9();
        Unknown00 = NewCount;
    }
    ~cIntArray()
    {
        SetCount(0);
        if (m_CapacityBytes)
        {
            GetAllocator()->Virtual5(Unknown08);
            Unknown08 = 0;
            m_CapacityBytes = 0;
        }
    }
    cIntArray& operator=(const cIntArray& Other)
    {
        Unknown00 = 0;
        AppendAll(Other);
        return *this;
    }
    void AppendAll(const cIntArray& Other);
    void RemoveAt(int Index);
    int FindIndex(int Item)
    {
        for (int i = 0; i < Count; i++)
        {
            if (Data[i] == Item)
                return i;
        }
        return -1;
    }
    int FindTarget(Class_10978090Result* Item)
    {
        for (int i = 0; i < Count; i++)
        {
            if (TargetData[i] == Item)
                return i;
        }
        return -1;
    }
    int FindOrAdd(const int* Item);
    void Clear();
    void CopyFrom(const cIntArray& Other);
    void InsertAt(int Index, int* Value);
    int Add(int* Item);
    void DeleteAll();
    void PushFront(const int* Item);
    void AddUnique(int Item);
    void Remove(int Item);
    void FUN_10c08690(struct Struct_10C08690* Item);

    union
    {
        int Unknown00;
        int Count;
    };
    int m_CapacityBytes;
    union
    {
        int* Unknown08;
        int* Data;
        Class_10978090Result** TargetData;
        float* FloatData;
    };
};

class Class_10978090 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual void Virtual5();
    virtual float Virtual6(int A);
    Class_10978090Result* FUN_10978090();
};

class Class_10BFD710 {
public:
    Class_10978090Result* FUN_10bfd220();
    int GetItemCount() { return ItemCount; }
    char Unknown00[8];
    int ItemCount;
    int ItemCapacityBytes;
    Class_10978090** Items;
};

extern float DAT_10eafbdc;

// FUNCTION: 0x10BFD220 ?FUN_10bfd220@Class_10BFD710@@QAEPAVClass_10978090Result@@XZ
Class_10978090Result* Class_10BFD710::FUN_10bfd220()
{
    cIntArray Targets;
    cIntArray Weights;
    for (int i = 0; i < GetItemCount(); ++i) {
        Class_10978090* Item = Items[i];
        if (Item->FUN_10978090()) {
            Class_10978090Result* Target = Item->FUN_10978090();
            int Index = Targets.FindTarget(Target);
            float Weight = Item->Virtual6(0);
            if (Weight > 0.1f) {
                if (Index == -1) {
                    Class_10978090Result* Added = Item->FUN_10978090();
                    int Pos = Targets.Count;
                    Targets.SetCount(Pos + 1);
                    Targets.TargetData[Pos] = Added;
                    Pos = Weights.Count;
                    Weights.SetCount(Pos + 1);
                    Weights.FloatData[Pos] = Weight;
                } else {
                    Weights.FloatData[Index] += Weight;
                }
            }
        }
    }
    Class_10978090Result* Best = 0;
    float BestWeight = DAT_10eafbdc;
    for (int k = 0; k < Weights.Count; ++k) {
        if (BestWeight < Weights.FloatData[k]) {
            BestWeight = Weights.FloatData[k];
            Best = Targets.TargetData[k];
        }
    }
    return Best;
}
