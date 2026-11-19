// Game/ObjectResultPositions.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cObjectArray.h"
#include "Game/Class_10C1AC00.h"

class Class_10978090Result;

class Class_10978090
{
public:
    virtual int Virtual0();
    virtual void Virtual1(FVector* Position, float* Value);
    Class_10978090Result* FUN_10978090();
};

class Class_10FF667C
{
public:
    char Unknown00[0x40];
    int Unknown40;
    char Unknown44[12];
    int Unknown50;
};

extern Class_10FF667C* DAT_10ff667c;

struct ObjectPositionEntry
{
    virtual void Virtual0();
    Class_10978090Result* Result;
    FVector Position;
};

T3_CHECK_SIZE(ObjectPositionEntry, 20);

class ObjectResultPositions
{
public:
    void Update(Class_10978090* Object, bool Flag);
    char Unknown00[0x54];
    cObjectArray Entries;
};

// FUNCTION: 0x10BFD860 ?Update@ObjectResultPositions@@QAEXPAVClass_10978090@@_N@Z
void ObjectResultPositions::Update(Class_10978090* Object, bool Flag)
{
    int Index = -1;
    Class_10978090Result* Result = Object->FUN_10978090();
    cObjectArray* List = &Entries;
    for (int i = 0; i < Entries.m_Count; ++i)
    {
        if (((ObjectPositionEntry*)Entries.m_Data)[i].Result == Result)
        {
            Index = i;
            break;
        }
    }
    float Value = 0.0f;
    FVector Position(0.0f, 0.0f, 0.0f);
    if (Index >= 0)
        Position = ((ObjectPositionEntry*)Entries.m_Data)[Index].Position;
    switch (Object->Virtual0())
    {
    case 4:
    case 6:
        break;
    case 8:
        if (!Flag)
            Object->Virtual1(&Position, &Value);
        break;
    case 7:
        {
            int Kind;
            ((Class_10C1AC00*)Object)->FUN_10c1ac00(&Kind);
            if ((Kind != DAT_10ff667c->Unknown50 || !Flag) && Kind != DAT_10ff667c->Unknown40)
                Object->Virtual1(&Position, &Value);
        }
        break;
    default:
        Object->Virtual1(&Position, &Value);
        break;
    }
    if (Index == -1)
    {
        ObjectPositionEntry New;
        New.Result = Result;
        New.Position = Position;
        int NewIndex = List->m_Count;
        List->SetCount(NewIndex + 1);
        ObjectPositionEntry* Entry = &((ObjectPositionEntry*)List->m_Data)[NewIndex];
        *Entry = New;
    }
    else
        ((ObjectPositionEntry*)Entries.m_Data)[Index].Position = Position;
}
