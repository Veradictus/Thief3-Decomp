// Game/FactionRelationQuery.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10905A90_Member.h"
#include "Game/Class_10B9BCA0.h"
#include "Game/Class_10BAC050.h"
#include "Game/Class_10BABED0.h"

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

// Target-local actor prefix: slot 34, Location at 0x2c, Controller at 0xc0.
class Class_10BAA6B0_Param {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual int Virtual34();
    char Unknown04[0x28];
    FVector Location;
    char Unknown38[0x88];
    UObject* Controller;
};

class RelationModel {
public:
    int FUN_10baac90(Class_10BAA6B0_Param* Actor);
};

class AAIPawn;

Class_10BABED0* FUN_10baa6b0(Class_10BAA6B0_Param* Actor);

Class_10B9BCA0* GetAIPawnController(AAIPawn* Actor);

struct Struct_10B9BCA0 {
    char Unknown00[0x10];
    Class_10BAC050* Unknown10;
};

class Class_10C1A170_Filter {
public:
    virtual char Virtual0(int Actor);
};

class Class_10E98CE8 : public Class_10C1A170_Filter {
public:
    Class_10E98CE8(Class_10BAC050* Model, int Kind);
    Class_10BAC050* Unknown04;
    int Unknown08;
};

class Class_10E98CE0 : public Class_10C1A170_Filter {
public:
    Class_10E98CE0(Class_10C1A170_Filter* Left, Class_10C1A170_Filter* Right);
    Class_10C1A170_Filter* Unknown04;
    Class_10C1A170_Filter* Unknown08;
};

// The global getter returns the retained four-byte counter allocation.
// The query entry point does not read its receiver.
class Class_10C1A160 {
public:
    void FUN_10c1a310(cIntArray* Out, FVector* Center, float Radius, Class_10C1A170_Filter* Filter, float Dist);
};

Class_10C1A160* GetCounter();

// FUNCTION: 0x10BAC100 ?FUN_10bac100@@YAXPAVcIntArray@@PAVClass_10BAA6B0_Param@@MM@Z
void FUN_10bac100(cIntArray* Out, Class_10BAA6B0_Param* Target, float Radius, float Dist)
{
    if (!Target->Virtual34() && Target->Controller) {
        Class_10BAC050* Model = (Class_10BAC050*)FUN_10baa6b0(Target);
        if (Model) {
            Class_10E98CE8 Four(Model, 4);
            Class_10E98CE8 Three(Model, 3);
            Class_10E98CE0 Either(&Four, &Three);
            GetCounter()->FUN_10c1a310(Out, &Target->Location, Radius * 16.0f, &Either, Dist * 16.0f);
        }
        return;
    }
    cIntArray Nearby;
    GetCounter()->FUN_10c1a310(&Nearby, &Target->Location, Radius * 16.0f, 0, Dist * 16.0f);
    for (int i = 0; i < Nearby.Count; ++i) {
        Class_10BAA6B0_Param* Actor = Nearby.ActorData[i];
        if (Actor && Actor->Controller && !Actor->Virtual34()) {
            Class_10B9BCA0* Controller = GetAIPawnController((AAIPawn*)Actor);
            if (Controller && Controller->Unknown118 && Controller->Unknown118->Unknown10) {
                int Kind = ((RelationModel*)Controller->Unknown118->Unknown10)->FUN_10baac90(Target);
                if (Kind == 4 || Kind == 3) {
                    Class_10BAA6B0_Param* const& Found = Nearby.ActorData[i];
                    int Index = Out->Count;
                    Out->SetCount(Index + 1);
                    Out->ActorData[Index] = Found;
                }
            }
        }
    }
}
