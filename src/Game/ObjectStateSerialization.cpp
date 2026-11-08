// Game/ObjectStateSerialization.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/FArchive.h"
#include "Game/cIntArray.h"
#include "Game/Class_10953AC0.h"
#include "Game/Class_10FF667C.h"
#include "Game/Class_10FF667C_Unknown18.h"

class cString;

class Class_10F352D8_Result;

class Class_10F352D8
{
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
    virtual void Virtual15(const cString& Ref);
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual Class_10F352D8_Result* Virtual22(int Key);
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31(FArchive& Ar, int* Value);
};

extern Class_10F352D8* DAT_10f352d8;

extern Class_10FF667C* DAT_10ff667c;

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

FArchive& FUN_10b052a0(FArchive& Ar, void* Data);

class Class_10E98C8C {
public:
    virtual void Serialize(FArchive& Ar);
    Class_10E98C8C(int Value);
    int Unknown04;
};

class Serializer739 {
public:
    virtual void Virtual0();
    virtual void Virtual1(FArchive& Ar, int* Value);
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(FArchive& Ar, int* Value);
};

class EmbeddedSerializer16 {
public:
    virtual void Serialize(FArchive& Ar);
    char Unknown04[0xC];
};

class EmbeddedSerializer8 {
public:
    virtual void Serialize(FArchive& Ar);
    int Unknown04;
};

struct Record739 { int Key; char Payload[12]; };

class Class_10BAB250 {
public:
    void FUN_10bab250(FArchive& Ar);
    char Unknown00[0x44];
    Serializer739* Unknown44;
    int Unknown48;
    int Unknown4C;
    unsigned char Unknown50;
    char Pad51[3];
    EmbeddedSerializer16 Unknown54;
    unsigned char Unknown64;
    unsigned char Unknown65;
    char Pad66[2];
    int Unknown68, Unknown6C, Unknown70;
    cIntArray Objects;
    int Unknown80, Unknown84, Unknown88, Unknown8C;
    char Unknown90[12];
    char Unknown9C[12];
    EmbeddedSerializer8 UnknownA8;
    int UnknownB0;
    unsigned char UnknownB4;
    char PadB5[3];
    char UnknownB8[12];
    int UnknownC4, UnknownC8;
    Class_10953AC0 Records;
    cIntArray References;
    char PadE4[0x7C];
    int Unknown160;
};

// FUNCTION: 0x10BAB250 ?FUN_10bab250@Class_10BAB250@@QAEXAAVFArchive@@@Z
void Class_10BAB250::FUN_10bab250(FArchive& Ar)
{
    Unknown44->Virtual1(Ar, &Unknown48);
    Ar.Serialize(&Unknown4C, 4);
    Ar.Serialize(&Unknown50, 1);
    Unknown54.Serialize(Ar);
    Ar.Serialize(&Unknown64, 1);
    Ar.Serialize(&Unknown65, 1);
    Ar.Serialize(&Unknown68, 4);
    Ar.Serialize(&Unknown6C, 4);
    Ar.Serialize(&Unknown70, 4);
    int ObjectCount = Objects.Count;
    Ar.Serialize(&ObjectCount, 4);
    if (Ar.Unknown14)
        Objects.SetCount(ObjectCount);
    for (int i = 0; i < ObjectCount; ++i) {
        if (Ar.Unknown14)
            Objects.Data[i] = (int)new(0, 0, 0, 0, 0) Class_10E98C8C(0);
        ((Class_10E98C8C*)Objects.Data[i])->Serialize(Ar);
    }
    Ar.Virtual7(&Unknown80);
    Ar.Virtual7(&Unknown84);
    Ar.Serialize(&Unknown88, 4);
    Ar.Serialize(&Unknown8C, 4);
    FUN_10b052a0(Ar, Unknown90);
    FUN_10b052a0(Ar, Unknown9C);
    UnknownA8.Serialize(Ar);
    Ar.Serialize(&UnknownB0, 4);
    Ar.Serialize(&UnknownB4, 1);
    FUN_10b052a0(Ar, UnknownB8);
    Ar.Serialize(&UnknownC4, 4);
    Ar.Serialize(&UnknownC8, 4);
    int RecordCount = Records.m_Count;
    Ar.Serialize(&RecordCount, 4);
    if (Ar.Unknown14)
        Records.Resize(RecordCount);
    for (int j = 0; j < RecordCount; ++j) {
        Unknown44->Virtual1(Ar, &((Record739*)Records.m_Items)[j].Key);
        FUN_10b052a0(Ar, ((Record739*)Records.m_Items)[j].Payload);
    }
    int ReferenceCount = References.Count;
    Ar.Serialize(&ReferenceCount, 4);
    if (Ar.Unknown14)
        References.SetCount(ReferenceCount);
    for (int k = 0; k < ReferenceCount; ++k)
        DAT_10ff667c->Unknown18->Virtual1(Ar, &References.Data[k]);
    if (Ar.Unknown0C >= 0x80)
        DAT_10f352d8->Virtual31(Ar, &Unknown160);
}
