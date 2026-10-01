// Game/Unsorted_10BC4BF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E91CB8 : public Class_10E8BE68
{
public:
    virtual void FUN_10bcb7f0(FArchive& Ar);

    char Unknown04[0x3C];
    float Unknown40[3];
};

// FUNCTION: 0x10BCB7F0 ?FUN_10bcb7f0@Class_10E91CB8@@UAEXAAVFArchive@@@Z
void Class_10E91CB8::FUN_10bcb7f0(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    FUN_10b052a0(Ar, Unknown40);
}
