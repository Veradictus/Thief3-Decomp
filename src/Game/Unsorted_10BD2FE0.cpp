// Game/Unsorted_10BD2FE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E935F0 : public Class_10E8BE68
{
public:
    virtual void FUN_10bd3090(FArchive& Ar);

    char Unknown04[0x40];
    int Unknown44;
    float Unknown48[3];
};

// FUNCTION: 0x10BD3090 ?FUN_10bd3090@Class_10E935F0@@UAEXAAVFArchive@@@Z
void Class_10E935F0::FUN_10bd3090(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    Ar.Serialize(&Unknown44, 4);
    FUN_10b052a0(Ar, Unknown48);
}
