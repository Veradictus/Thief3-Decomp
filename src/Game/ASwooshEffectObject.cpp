// Game/ASwooshEffectObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e55b48[];

class AActor
{
public:
    AActor* FUN_1098cf10();

    void** Unknown00;
};

class AMetaProperty : public AActor
{
};

class ASwooshEffectObject : public AMetaProperty
{
public:
    ASwooshEffectObject();
};

// FUNCTION: 0x1099BAA0 ??0ASwooshEffectObject@@QAE@XZ
ASwooshEffectObject::ASwooshEffectObject()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e55b48;
}
