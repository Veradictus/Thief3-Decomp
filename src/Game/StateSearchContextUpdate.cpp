// Game/StateSearchContextUpdate.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10C08940;

class Class_10C1AC00;

// Local physical views; no shared virtual declarations or object layouts change.
class Class_10978090
{
public:
    virtual int Kind();
    virtual bool ReadLocation(FVector* Position, float* Extra);
    Class_10C08940* FUN_10978090();
};

class Class_10BFC110
{
public:
    Class_10978090* FindBestFor(Class_10C08940* Owner);
};

class Class_10C88610
{
public:
    Class_10C1AC00* FUN_10c88610();
};

class Class_10C1AC00
{
public:
    int* FUN_10c1ac00(int* Out);
};

class Class_10C08940
{
public:
    char Opaque00[0x2C];
    FVector Location;
};

class Class_10FF667C
{
public:
    char Opaque00[0x50];
    int Unknown50;
};

extern Class_10FF667C* DAT_10ff667c;

struct SearchContextOwner353
{
    char Opaque00[0x30];
    Class_10BFC110 Contexts;
};

class State_Search
{
public:
    virtual void OpaqueSlot0();
    void FUN_10bd20f0(Class_10C08940* Target);

    SearchContextOwner353* Owner;
    char Opaque08[0xFC];
    Class_10C08940* SavedTarget;
    FVector SavedPosition;
};

// FUNCTION: 0x10BD20F0 ?FUN_10bd20f0@State_Search@@QAEXPAVClass_10C08940@@@Z
void State_Search::FUN_10bd20f0(Class_10C08940* Target)
{
    Class_10BFC110* Contexts = &Owner->Contexts;
    Class_10978090* Context = Contexts->FindBestFor(Target);
    Class_10978090* Current = (Class_10978090*)((Class_10C88610*)Contexts)->FUN_10c88610();
    if (Current && Current->FUN_10978090() == Target)
        Context = Current;
    if (!Context)
        return;

    if (Context->Kind() == 2 || Context->Kind() == 3 || Context->Kind() == 1 || Context->Kind() == 7)
    {
        FVector Position(0.0f, 0.0f, 0.0f);
        float Extra;
        Context->ReadLocation(&Position, &Extra);
        SavedPosition = Position;
        SavedTarget = Target;
        if (Context->Kind() == 7)
        {
            int* CurrentId = &DAT_10ff667c->Unknown50;
            int Id;
            int* IdResult = ((Class_10C1AC00*)Context)->FUN_10c1ac00(&Id);
            if (*IdResult == *CurrentId)
            {
                SavedTarget = Target;
                SavedPosition = Target->Location;
                return;
            }
        }
    }
    if (Context->Kind() == 9 || Context->Kind() == 10 || Context->Kind() == 11 || Context->Kind() == 12)
    {
        SavedTarget = Target;
        SavedPosition = Target->Location;
    }
}
