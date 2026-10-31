// Game/LockPickPinPositions.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10AF4BB0.h"
#include "Game/Class_10943600.h"
#include <math.h>

class Class_1098E3D0;

struct LockPickRange
{
    float MinRadius;
    float MaxRadius;
    int MinAngle;
    int MaxAngle;
};

// Existing folded empty hook alias (native10D660B0 is RET). This view has no fields.
class Class_10D660B0
{
public:
    void FUN_10d660b0();
};

class LockPickInnerArray : public Class_10AF4BB0
{
public:
    int Num() const { return Unknown04; }
    LockPickRange& operator()(int Index) { return ((LockPickRange*)Unknown00)[Index]; }
    ~LockPickInnerArray()
    {
        ((Class_10D660B0*)this)->FUN_10d660b0();
        FUN_10af3bd0(0, Num(), 16);
    }
};

// Canonical property-array type witnessed by native destructor 10AD01A0.
class Class_10AD01A0 : public Class_10AF4BB0
{
public:
    int Num() const { return Unknown04; }
    ~Class_10AD01A0()
    {
        ((Class_10D660B0*)this)->FUN_10d660b0();
        RemoveOwned(0, Num());
    }
    void RemoveOwned(int Index, int Count)
    {
        for (int i = Index; i < Index + Count; i++)
            ((LockPickInnerArray*)Unknown00)[i].~LockPickInnerArray();
        FUN_10af3bd0(Index, Count, 12);
    }
};

// External property result: owned nested array header followed by a scalar index.
class Class_10AD0200 : public Class_10AD01A0
{
public:
    int Index;
};

T3_CHECK_SIZE(LockPickInnerArray, 12);

T3_CHECK_SIZE(Class_10AD01A0, 12);

T3_CHECK_SIZE(Class_10AD0200, 16);

class Class_10ACF3A0
{
public:
    void FUN_10acfb10(int Actor, void* Out);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0xFC];
    Class_10ACF3A0* UnknownFC;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10B3F830_Arg
{
public:
    char Unknown00[0x458];
    Class_1098E3D0* Unknown458;
};

T3_CHECK_SIZE(LockPickRange, 16);

class cLockPickController
{
public:
    void FUN_10b3f3c0(Class_10B3F830_Arg* A);
    char Unknown00[0x10];
    Class_10943600 PinPositions;
};

int FUN_10af3a20();

float appFrand();

// FUNCTION: 0x10B3F3C0 ?FUN_10b3f3c0@cLockPickController@@QAEXPAVClass_10B3F830_Arg@@@Z
void cLockPickController::FUN_10b3f3c0(Class_10B3F830_Arg* A)
{
    Class_10AD0200 Info;
    DAT_10f3a3d8->UnknownFC->FUN_10acfb10((int)A->Unknown458, &Info);
    int Count = Info.Unknown04;
    PinPositions.FUN_10da4f50(Count);
    for (int i = 0; i < Count; ++i)
    {
        LockPickInnerArray& Choices = ((LockPickInnerArray*)Info.Unknown00)[i];
        LockPickRange& Range = Choices(FUN_10af3a20() % Choices.Num());
        if (Range.MinRadius < 0.1f)
            Range.MinRadius = 0.1f;
        if (Range.MaxRadius < 0.1f)
            Range.MaxRadius = 0.1f;
        int Angle = Range.MinAngle + FUN_10af3a20() % (Range.MaxAngle - Range.MinAngle + 1);
        float Radius = appFrand() * (Range.MaxRadius - Range.MinRadius) + Range.MinRadius;
        double Radians = Angle * (3.14159265358979323846 / 180.0);
        double Sine = sin(Radians);
        double Cosine = cos(Radians);
        ((FVector*)PinPositions.Unknown08)[i] = FVector((float)Sine, (float)Cosine, 0.0f);
        FVector& Position = ((FVector*)PinPositions.Unknown08)[i];
        Position.X *= Radius;
        Position.Y *= Radius;
        Position.Z *= Radius;
    }
}
