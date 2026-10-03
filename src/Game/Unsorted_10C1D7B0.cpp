// Game/Unsorted_10C1D7B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6(int* Value);
    virtual void Virtual7(int* Value);
};

class Class_10E8D7C4
{
public:
    virtual void FUN_10c1ef20(FArchive& Ar);

    int Unknown04;
    int Unknown08;
    char Unknown0C;
};

// FUNCTION: 0x10C1EF20 ?FUN_10c1ef20@Class_10E8D7C4@@UAEXAAVFArchive@@@Z
void Class_10E8D7C4::FUN_10c1ef20(FArchive& Ar)
{
    Ar.Virtual6(&Unknown04);
    Ar.Virtual7(&Unknown08);
    Ar.Serialize(&Unknown0C, 1);
}
