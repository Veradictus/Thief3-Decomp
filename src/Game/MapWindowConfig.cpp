// Game/MapWindowConfig.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10905A90_Member.h"
#include "Game/Window.h"
#include "Game/Config.h"
#include "Game/Class_10AF7F80.h"
#include "Game/cString.h"

class Class_10E6CE28;

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
        Class_10E6CE28** LinkData;
    };
};

class Class_10B65E90_Unknown200;

class Class_10E84978;

class WindowManager
{
public:
    Class_10B65E90_Unknown200* FUN_109e6f40(cString*, Class_10E84978*);
    Class_10B65E90_Unknown200* FUN_109e7cb0(Class_10E84978*, Class_10AF7F80*, const FString&);
};

extern WindowManager* GWindowManager;

struct MapWindowChildren
{
    char Unknown00[0xB8];
    cIntArray Children;
};

class MapWindowConfig : public Window
{
public:
    void Load(Class_10AF7F80* File, Class_10AF7F80* Section);
    Class_10B65E90_Unknown200* Child;
    void* Actor;
};

T3_CHECK_SIZE(Window, 0x118);

// FUNCTION: 0x10B54CE0 ?Load@MapWindowConfig@@QAEXPAVClass_10AF7F80@@0@Z
void MapWindowConfig::Load(Class_10AF7F80* File, Class_10AF7F80* Section)
{
    Window::LoadConfig(File, Section);
    cString Name;
    if (Config::Instance()->GetString(**Section, "CompassWindow", &Name.Unknown00, **File))
    {
        Class_10B65E90_Unknown200* Found = GWindowManager->FUN_109e6f40(&Name, (Class_10E84978*)this);
        if (!Found)
        {
            Found = GWindowManager->FUN_109e7cb0((Class_10E84978*)this, File, FString(*Name));
            cIntArray* Children = &((MapWindowChildren*)this)->Children;
            int Index = Children->Count;
            Children->SetCount(Index + 1);
            Children->Data[Index] = (int)Found;
        }
        Child = Found;
    }
    else
        Child = 0;
    Actor = 0;
}
