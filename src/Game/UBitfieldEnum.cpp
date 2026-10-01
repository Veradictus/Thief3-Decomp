// Game/UBitfieldEnum.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

FArchive& FUN_109bc520(FArchive& Ar, void* V);

class Class_10E4E590
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
    virtual void FUN_10ae5090(FArchive& Ar);
};

class UBitfieldEnum : public Class_10E4E590
{
public:
    virtual void FUN_10ad73f0(FArchive& Ar);

    char Unknown04[0x30];
    int Unknown34[3];
};

// FUNCTION: 0x10AD73F0 ?FUN_10ad73f0@UBitfieldEnum@@UAEXAAVFArchive@@@Z
void UBitfieldEnum::FUN_10ad73f0(FArchive& Ar)
{
    Class_10E4E590::FUN_10ae5090(Ar);
    FUN_109bc520(Ar, Unknown34);
    FUN_109bc520(Ar, Unknown34);
}
