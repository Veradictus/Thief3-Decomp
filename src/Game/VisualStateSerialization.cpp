// Game/VisualStateSerialization.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/FArchive.h"
#include "Game/cIntArray.h"
#include "Game/Class_10E99370.h"
#include "Game/cVisualSubsystemArray.h"

// Actual record slot zero is the existing archive operation, not deletion.
class VisualSubsystem
{
public:
    virtual void FUN_10c16d20(FArchive& Ar);
    VisualSubsystem(const VisualSubsystem& Other);
    VisualSubsystem() { Unknown04 = 0; }
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
};

// Physical owner projection; no construction or vtable object is emitted.
class Class_10E98CA4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10c17450(FArchive& Ar);
    virtual void Virtual3();
    virtual void ClearReferences(void* Object);
    void* Owner;
    int BaseValue;
    int Opaque0C;
    cIntArray ObjectsA;
    cIntArray ObjectsB;
    cIntArray ObjectsC;
    int Field34;
    int Field38;
    char Opaque3C[8];
    int Field44;
    int Field48;
    int Field4C;
    int Field50;
    int Field54;
    int Field58;
    VisualSubsystem Embedded;
    cVisualSubsystemArray Records;
    int Field98;
    int Field9C;
    int FieldA0;
    void* OpaqueA4;
    int OpaqueA8;
    int FieldAC;
    int FieldB0;
};

// FUNCTION: 0x10C17450 ?FUN_10c17450@Class_10E98CA4@@UAEXAAVFArchive@@@Z
void Class_10E98CA4::FUN_10c17450(FArchive& Ar)
{
    ((Class_10E99370*)this)->Class_10E99370::FUN_10c28280((Class_10C28280_Param*)&Ar);
    Ar.Serialize(&Field34, 4);
    Ar.Serialize(&Field38, 4);
    Ar.Serialize(&Field44, 4);
    Ar.Serialize(&Field48, 4);
    Ar.Serialize(&Field4C, 4);
    Ar.Serialize(&Field50, 4);
    Ar.Serialize(&Field54, 4);
    Ar.Serialize(&Field58, 4);
    Embedded.FUN_10c16d20(Ar);
    int RecordCount = Records.m_Count;
    Ar.Serialize(&RecordCount, 4);
    if (Ar.Unknown14)
        Records.Resize(RecordCount);
    for (int Index = 0; Index < RecordCount; ++Index)
        Records.m_Items[Index].FUN_10c16d20(Ar);
    Ar.Serialize(&Field98, 4);
    Ar.Serialize(&Field9C, 4);
    Ar.Serialize(&FieldA0, 4);

    int CountA = ObjectsA.Count;
    Ar.Serialize(&CountA, 4);
    if (Ar.Unknown14)
        ObjectsA.SetCount(CountA);
    for (int Index = 0; Index < CountA; ++Index)
        Ar.Virtual6((UObject**)&ObjectsA.Data[Index]);

    int CountB = ObjectsB.Count;
    Ar.Serialize(&CountB, 4);
    if (Ar.Unknown14)
        ObjectsB.SetCount(CountB);
    for (int Index = 0; Index < CountB; ++Index)
        Ar.Virtual6((UObject**)&ObjectsB.Data[Index]);

    int CountC = ObjectsC.Count;
    Ar.Serialize(&CountC, 4);
    if (Ar.Unknown14)
        ObjectsC.SetCount(CountC);
    for (int Index = 0; Index < CountC; ++Index)
        Ar.Virtual6((UObject**)&ObjectsC.Data[Index]);
    if (Ar.Unknown0C >= 0x31)
    {
        Ar.Serialize(&FieldAC, 4);
        Ar.Serialize(&FieldB0, 4);
    }
}
