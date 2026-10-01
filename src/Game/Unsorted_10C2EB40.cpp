// Game/Unsorted_10C2EB40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

FArchive& FUN_10b052a0(FArchive& Ar, void* V);

class Class_10C271A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();

    void FUN_10c271a0(FArchive& Ar);
};

class Class_10E9AA7C : public Class_10C271A0
{
public:
    virtual void FUN_10c2eb90(FArchive& Ar);

    char Unknown04[0x48];
    float Unknown4C[3];
};

// FUNCTION: 0x10C2EB90 ?FUN_10c2eb90@Class_10E9AA7C@@UAEXAAVFArchive@@@Z
void Class_10E9AA7C::FUN_10c2eb90(FArchive& Ar)
{
    FUN_10c271a0(Ar);
    FUN_10b052a0(Ar, Unknown4C);
}
