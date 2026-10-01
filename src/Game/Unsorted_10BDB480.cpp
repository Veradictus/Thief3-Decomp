// Game/Unsorted_10BDB480.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

class Class_10E8BE68
{
public:
    virtual void FUN_10bca010(FArchive& Ar);
};

class Class_10E948D8 : public Class_10E8BE68
{
public:
    virtual void FUN_10bdba50(FArchive& Ar);

    char Unknown04[0x50];
    int Unknown54;
};

// FUNCTION: 0x10BDBA50 ?FUN_10bdba50@Class_10E948D8@@UAEXAAVFArchive@@@Z
void Class_10E948D8::FUN_10bdba50(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    Ar.Serialize(&Unknown54, 4);
}
