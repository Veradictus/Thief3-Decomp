// Game/Unsorted_10C1B290.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
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

class Class_10E98DE0 : public Class_10C1B1A0
{
public:
    virtual void FUN_10c1b300(FArchive& Ar);

    char Unknown04[0x44];
    float Unknown48[3];
    int Unknown54;
};

// FUNCTION: 0x10C1B300 ?FUN_10c1b300@Class_10E98DE0@@UAEXAAVFArchive@@@Z
void Class_10E98DE0::FUN_10c1b300(FArchive& Ar)
{
    FUN_10c1b1a0(Ar);
    FUN_10b052a0(Ar, Unknown48);
    Ar.Serialize(&Unknown54, 4);
}
