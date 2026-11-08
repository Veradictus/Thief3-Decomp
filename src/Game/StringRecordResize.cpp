// Game/StringRecordResize.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cString.h"
#include "Game/Class_10ABDAE0.h"

class Class_10B1A7D0Item
{
public:
    int Unknown00;
    int Unknown04;
    cString Unknown08;
};

// FUNCTION: 0x10ABDAE0 ?SetCount@Class_10ABDAE0@@QAEXH@Z
void Class_10ABDAE0::SetCount(int Count)
{
    int OldCount = m_Count;
    int Capacity = !m_Data ? 0 : Unknown04 / sizeof(Class_10B1A7D0Item);
    for (int I = Count; I < OldCount; ++I)
        m_Data[I].Unknown08.Class_1090A780::~Class_1090A780();
    GetAllocator()->Virtual8(0, 0);
    if (Count > Capacity)
    {
        int NewCapacity = Count;
        if (Capacity)
            NewCapacity = (Count & ~15) + 16;
        m_Data = (Class_10B1A7D0Item*)GetAllocator()->Virtual3(m_Data, NewCapacity * sizeof(Class_10B1A7D0Item), 0, 0, 0, 0);
        Unknown04 = NewCapacity * sizeof(Class_10B1A7D0Item);
    }
    else if (Count <= Capacity - 16)
    {
        if (Count == 0)
        {
            GetAllocator()->Virtual5(m_Data);
            m_Data = 0;
            Unknown04 = 0;
        }
        else
        {
            int NewCapacity = (Count & ~15) + 16;
            m_Data = (Class_10B1A7D0Item*)GetAllocator()->Virtual3(m_Data, NewCapacity * sizeof(Class_10B1A7D0Item), 0, 0, 0, 0);
            Unknown04 = NewCapacity * sizeof(Class_10B1A7D0Item);
        }
    }
    for (int I = OldCount; I < Count; ++I)
    {
        Class_10B1A7D0Item* Item = m_Data + I;
        if (Item)
        {
            Item->Unknown08.Unknown00 = 0;
            Item->Unknown00 = 0;
            Item->Unknown04 = 0;
        }
    }
    GetAllocator()->Virtual9();
    m_Count = Count;
}
