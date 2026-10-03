// Game/Unsorted_10C1B750.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);

    char Unknown04[8];
    int Unknown0C;
};

class Object_10BFBD00
{
public:
    virtual void Virtual0();
    virtual void Virtual1(FArchive& Ar, void* Value);
};

class Class_10FF667C
{
public:
    char Unknown00[0x18];
    Object_10BFBD00* Unknown18;
};

extern Class_10FF667C* DAT_10ff667c;

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

class Class_10E98FD8 : public Class_10C1B1A0
{
public:
    virtual void FUN_10c1b790(FArchive& Ar);

    char Unknown04[0x44];
    int Unknown48;
    void* Unknown4C;
};

// FUNCTION: 0x10C1B790 ?FUN_10c1b790@Class_10E98FD8@@UAEXAAVFArchive@@@Z
void Class_10E98FD8::FUN_10c1b790(FArchive& Ar)
{
    FUN_10c1b1a0(Ar);
    Ar.Serialize(&Unknown48, 4);
    if (Ar.Unknown0C >= 0x6a)
        DAT_10ff667c->Unknown18->Virtual1(Ar, &Unknown4C);
}
