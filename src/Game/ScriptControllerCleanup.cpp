// Game/ScriptControllerCleanup.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Engine/EngineClasses.h"
#include "AICore/AICoreClasses.h"
#include "Game/Class_10905A90_Member.h"
#include "Game/Class_10A7F5A0.h"
#include "Game/Class_10A9DBE0_Param2.h"
#include "Game/Class_10A9DBE0_Param3.h"

class Class_10BAA6B0_Param;

Class_10905A90_Member* GetAllocator();

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
        Class_10BAA6B0_Param** ActorData;
    };
};

class Class_10B9BDB0 { public: void FUN_10b9bf60(); };

class Class_10BA9EC0 { public: void* FUN_10ba9ec0(); };

class Class_10C01CE0 { public: void RemoveAll(); };

struct FlagOwner390 { int Unknown00; bool Unknown04; };

struct ControllerData390 {
    int Unknown00;
    FlagOwner390* Owner;
    int Unknown08;
    int Unknown0C;
    Class_10BA9EC0* Model;
};

class ControllerView390 { public: char Unknown00[0x118]; ControllerData390* Data; };

class Class_10BB25F0 {
public:
    int FUN_10bb25f0(int A, Class_10A9DBE0_Param2* B, Class_10A9DBE0_Param3* C);
};

// FUNCTION: 0x10BB25F0 ?FUN_10bb25f0@Class_10BB25F0@@QAEHHPAVClass_10A9DBE0_Param2@@PAVClass_10A9DBE0_Param3@@@Z
int Class_10BB25F0::FUN_10bb25f0(int A, Class_10A9DBE0_Param2* B, Class_10A9DBE0_Param3* C)
{
    cIntArray Found = C->Virtual4(0)->FUN_10a7f5a0(B->Virtual8(), 0);
    for (unsigned Remaining = Found.Count; Remaining > 0; --Remaining) {
        AAIPawn* Pawn = Cast<AAIPawn>((UObject*)Found.Data[0]);
        ControllerData390* Data = ((ControllerView390*)Pawn->Controller)->Data;
        if (Data && Data->Owner) {
            Data->Owner->Unknown04 = true;
            ((Class_10B9BDB0*)Pawn->Controller)->FUN_10b9bf60();
            ((Class_10C01CE0*)Data->Model->FUN_10ba9ec0())->RemoveAll();
        }
    }
    return 1;
}
