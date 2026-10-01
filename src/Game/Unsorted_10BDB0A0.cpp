// Game/Unsorted_10BDB0A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

void FUN_10c11ff0(FArchive& Ar, int* Value);

class Class_10E94A00 : public Class_10E8BE68
{
public:
    virtual void FUN_10bdb210(FArchive& Ar);

    char Unknown04[0x50];
    int Unknown54;
};

// FUNCTION: 0x10BDB210 ?FUN_10bdb210@Class_10E94A00@@UAEXAAVFArchive@@@Z
void Class_10E94A00::FUN_10bdb210(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    FUN_10c11ff0(Ar, &Unknown54);
}
