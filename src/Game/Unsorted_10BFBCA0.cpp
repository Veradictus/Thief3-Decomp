// Game/Unsorted_10BFBCA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

FArchive& FUN_10b052a0(FArchive& Ar, void* Value);

class Object_10BFBD00
{
public:
    virtual void Virtual0();
    virtual void Virtual1(FArchive& Ar, void* Value);
};

class Class_10FF667C
{
public:
    char Unknown00[0x18];
    Object_10BFBD00* Unknown18;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10E8D7C0
{
public:
    virtual void FUN_10bfbd00(FArchive& Ar);

    int Unknown04;
    int Unknown08;
};

class Class_10E97A54
{
public:
    virtual void FUN_10bfbe60(FArchive& Ar);

    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10BFBD00 ?FUN_10bfbd00@Class_10E8D7C0@@UAEXAAVFArchive@@@Z
void Class_10E8D7C0::FUN_10bfbd00(FArchive& Ar)
{
    FUN_10b052a0(Ar, &Unknown08);
    DAT_10ff667c->Unknown18->Virtual1(Ar, &Unknown04);
}

// FUNCTION: 0x10BFBE60 ?FUN_10bfbe60@Class_10E97A54@@UAEXAAVFArchive@@@Z
void Class_10E97A54::FUN_10bfbe60(FArchive& Ar)
{
    Ar.Serialize(&Unknown04, 4);
    Ar.Serialize(&Unknown08, 4);
}
