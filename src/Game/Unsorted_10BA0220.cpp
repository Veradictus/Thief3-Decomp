// Game/Unsorted_10BA0220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA1270
{
public:
    virtual ~Class_10BA1270();
};

extern Class_10BA1270* DAT_10ff6680;

struct Struct_10BA12F0
{
    char Unknown00[0xC];
    int Count;
    char Unknown10[4];
    void** Items;
};

class Class_10BA12F0
{
public:
    void FUN_10ba12f0();

    void* Current;
    Struct_10BA12F0* Container;
    int Index;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);

    char Unknown04[8];
    int Unknown0C;
};

class Class_10C084A0
{
public:
    void FUN_10c084a0(FArchive& Ar);
};

class Class_10C074F0
{
public:
    void FUN_10c074f0(FArchive& Ar);
};

class Class_10E8C118
{
public:
    virtual void Virtual0();
    virtual void FUN_10ba0da0(FArchive& Ar);

    char Unknown04[0x28];
    Class_10C084A0* Unknown2C;
    Class_10C074F0* Unknown30;
    char Unknown34[0x7C];
    bool UnknownB0;
};

// FUNCTION: 0x10BA0DA0 ?FUN_10ba0da0@Class_10E8C118@@UAEXAAVFArchive@@@Z
void Class_10E8C118::FUN_10ba0da0(FArchive& Ar)
{
    if (Ar.Unknown0C >= 0x5E)
        Unknown2C->FUN_10c084a0(Ar);
    if (Ar.Unknown0C >= 0x66)
        Ar.Serialize(&UnknownB0, 1);
    if (Ar.Unknown0C >= 0x74)
        Unknown30->FUN_10c074f0(Ar);
}

// FUNCTION: 0x10BA1270 ?FUN_10ba1270@@YAXXZ
void FUN_10ba1270()
{
    if (DAT_10ff6680)
    {
        delete DAT_10ff6680;
        DAT_10ff6680 = 0;
    }
}

// FUNCTION: 0x10BA12F0 ?FUN_10ba12f0@Class_10BA12F0@@QAEXXZ
void Class_10BA12F0::FUN_10ba12f0()
{
    Index = -1;
    Current = 0;
    do {
        Index++;
        if (Index >= Container->Count) {
            Index = -1;
            return;
        }
        Current = Container->Items[Index];
    } while (Current == 0);
}
