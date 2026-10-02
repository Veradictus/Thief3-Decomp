// Game/Unsorted_10BCEA30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

FArchive& FUN_10b052a0(FArchive& Ar, void* V);

class Class_10E8BE68
{
public:
    virtual void FUN_10bca010(FArchive& Ar);
};

class Class_10E92B20 : public Class_10E8BE68
{
public:
    virtual void FUN_10bcea30(FArchive& Ar);

    char Unknown04[0x3C];
    float Unknown40[3];
    char Unknown4C;
};

// FUNCTION: 0x10BCEA30 ?FUN_10bcea30@Class_10E92B20@@UAEXAAVFArchive@@@Z
void Class_10E92B20::FUN_10bcea30(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    FUN_10b052a0(Ar, Unknown40);
    Ar.Serialize(&Unknown4C, 1);
}
