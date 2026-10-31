// Game/EventRecordMove.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cIntArray.h"

extern "C" void* memmove(void* Dest, const void* Src, unsigned Count);

struct EventRecord
{
    int Unknown00;
    cIntArray Values;
};

class Class_10ACB7A0
{
public:
    void MoveRange(int From, int To, int Count);
    int Unknown00;
    int Unknown04;
    EventRecord* m_Buffer;
};

// FUNCTION: 0x10ACB630 ?MoveRange@Class_10ACB7A0@@QAEXHHH@Z
void Class_10ACB7A0::MoveRange(int From, int To, int Count)
{
    if (From != To && Count != 0)
    {
        if (From < To)
        {
            for (int I = From + Count; I < To + Count; I++)
            {
                EventRecord* Item = m_Buffer + I;
                Item->Values.~cIntArray();
            }
        }
        else if (To < From)
        {
            for (int I = To; I < From; I++)
            {
                EventRecord* Item = m_Buffer + I;
                Item->Values.~cIntArray();
            }
        }
        memmove(m_Buffer + To, m_Buffer + From, Count * sizeof(EventRecord));
        if (From < To)
        {
            for (int I = From; I < To; I++)
            {
                EventRecord* Item = m_Buffer + I;
                if (Item)
                {
                    Item->Values.Count = 0;
                    Item->Values.m_CapacityBytes = 0;
                    Item->Values.Data = 0;
                }
            }
        }
        else
        {
            for (int I = To + Count; I < From + Count; I++)
            {
                EventRecord* Item = m_Buffer + I;
                if (Item)
                {
                    Item->Values.Count = 0;
                    Item->Values.m_CapacityBytes = 0;
                    Item->Values.Data = 0;
                }
            }
        }
    }
}
