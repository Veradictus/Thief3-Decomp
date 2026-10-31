// Game/LineRecordResize.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10905A90_Member.h"

Class_10905A90_Member* GetAllocator();

struct LineRecord
{
    float StartX;
    float StartY;
    float StartZ;
    float EndX;
    float EndY;
    float EndZ;
    unsigned char Color[4];
};

class LineRecordArray
{
public:
    void Resize(int Count);
    int m_Count;
    int m_CapacityBytes;
    LineRecord* m_Data;
};

// FUNCTION: 0x10B426A0 ?Resize@LineRecordArray@@QAEXH@Z
void LineRecordArray::Resize(int Count)
{
    int OldCount = m_Count;
    int Capacity = !m_Data ? 0 : m_CapacityBytes / sizeof(LineRecord);
    GetAllocator()->Virtual8(0, 0);
    if (Count > Capacity)
    {
        int NewCapacity = Count;
        if (Capacity)
            NewCapacity = (Count & ~15) + 16;
        m_Data = (LineRecord*)GetAllocator()->Virtual3(m_Data, NewCapacity * sizeof(LineRecord), 0, 0, 0, 0);
        m_CapacityBytes = NewCapacity * sizeof(LineRecord);
    }
    else if (Count <= Capacity - 16)
    {
        if (Count == 0)
        {
            GetAllocator()->Virtual5(m_Data);
            m_Data = 0;
            m_CapacityBytes = 0;
        }
        else
        {
            int NewCapacity = (Count & ~15) + 16;
            m_Data = (LineRecord*)GetAllocator()->Virtual3(m_Data, NewCapacity * sizeof(LineRecord), 0, 0, 0, 0);
            m_CapacityBytes = NewCapacity * sizeof(LineRecord);
        }
    }
    for (int I = OldCount; I < Count; I++)
    {
        LineRecord* Item = m_Data + I;
        if (Item)
        {
            Item->StartX = 0.0f;
            Item->StartY = 0.0f;
            Item->StartZ = 0.0f;
            Item->EndX = 0.0f;
            Item->EndY = 0.0f;
            Item->EndZ = 0.0f;
            Item->Color[0] = 255;
            Item->Color[1] = 255;
            Item->Color[2] = 255;
            Item->Color[3] = 255;
        }
    }
    GetAllocator()->Virtual9();
    m_Count = Count;
}
