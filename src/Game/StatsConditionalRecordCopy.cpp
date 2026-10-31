// Game/StatsConditionalRecordCopy.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cString.h"
#include "Game/Class_10A87F40.h"
#include "Game/Class_10A80FE0.h"
#include "Game/Class_10A174E0.h"

Class_10A174E0* GetStats();

struct Struct_10A80FE0_Element
{
    FName Name;
    int Expected;
};

struct Conditions272 : Class_10A80FE0
{
    Conditions272& operator=(const Conditions272& Source)
    {
        SetSize(Source.m_Size);
        for(int J=0;J<m_Size;++J) m_Elements[J]=Source.m_Elements[J];
        return *this;
    }
};

struct StatsRecord272
{
    cString A;
    cString B;
    cString C;
    Conditions272 Conditions;
};

class Class_10AA9C70
{
public:
    void FUN_10aa9c70(Class_10A87F40* Out);
    int Opaque00;
    int Opaque04;
    int Count;
    int Capacity;
    StatsRecord272* Data;
};

// FUNCTION: 0x10AA9C70 ?FUN_10aa9c70@Class_10AA9C70@@QAEXPAVClass_10A87F40@@@Z
void Class_10AA9C70::FUN_10aa9c70(Class_10A87F40* Out)
{
    Out->FUN_10a87cd0(0);
    for(int I=0;I<Count;++I)
    {
        bool Accept=true;
        for(int J=0;J<Data[I].Conditions.m_Size;++J)
            if(Data[I].Conditions.m_Elements[J].Name.Value)
                if(GetStats()->Virtual3(Data[I].Conditions.m_Elements[J].Name)!=Data[I].Conditions.m_Elements[J].Expected)
                    Accept=false;
        if(Accept)
        {
            int Index=Out->Unknown00;
            StatsRecord272* Source=Data+I;
            Out->FUN_10a87cd0(Index+1);
            StatsRecord272* Dest=(StatsRecord272*)Out->m_Data+Index;
            Dest->A=Source->A;
            Dest->B=Source->B;
            Dest->C=Source->C;
            Dest->Conditions=Source->Conditions;
        }
    }
}
