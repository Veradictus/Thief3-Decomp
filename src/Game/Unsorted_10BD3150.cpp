// Game/Unsorted_10BD3150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E934D0 : public Class_10E8BE68
{
public:
    virtual void FUN_10bd3150(FArchive& Ar);

    char Unknown04[0x40];
    int Unknown44;
};

// FUNCTION: 0x10BD3150 ?FUN_10bd3150@Class_10E934D0@@UAEXAAVFArchive@@@Z
void Class_10E934D0::FUN_10bd3150(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    Ar.Serialize(&Unknown44, 4);
}
