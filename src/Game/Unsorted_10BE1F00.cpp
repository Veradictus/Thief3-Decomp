// Game/Unsorted_10BE1F00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E959B0 : public Class_10E8BE68
{
public:
    virtual void FUN_10be20e0(FArchive& Ar);

    char Unknown04[0x3C];
    char Unknown40;
};

// FUNCTION: 0x10BE20E0 ?FUN_10be20e0@Class_10E959B0@@UAEXAAVFArchive@@@Z
void Class_10E959B0::FUN_10be20e0(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    Ar.Serialize(&Unknown40, 1);
}
