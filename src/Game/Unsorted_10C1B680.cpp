// Game/Unsorted_10C1B680.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

    char Unknown04[8];
    int Unknown0C;
};

FArchive& FUN_10b052a0(FArchive& Ar, void* V);

class Class_10C1B1A0
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

    void FUN_10c1b1a0(FArchive& Ar);
};

class Class_10E98F90 : public Class_10C1B1A0
{
public:
    virtual void FUN_10c1b710(FArchive& Ar);

    char Unknown04[0x44];
    int Unknown48;
    float Unknown4C[3];
};

// FUNCTION: 0x10C1B710 ?FUN_10c1b710@Class_10E98F90@@UAEXAAVFArchive@@@Z
void Class_10E98F90::FUN_10c1b710(FArchive& Ar)
{
    FUN_10c1b1a0(Ar);
    Ar.Virtual6(&Unknown48);
    if (Ar.Unknown0C >= 0x37)
        FUN_10b052a0(Ar, Unknown4C);
}
