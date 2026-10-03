// Game/Unsorted_10C1B7E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C1B930 {
public:
    char Unknown00[0x2C];
    int Unknown2C;
    char Unknown30[4];
    int Unknown34;
    char Unknown38[4];
    int Unknown3C;
    char Unknown40[7];
    unsigned char Unknown47;

    void FUN_10c1b930();
};

class UObject;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6(UObject** Value);

    char Unknown04[8];
    int Unknown0C;
};

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

class Class_10E98D50 : public Class_10C1B1A0
{
public:
    virtual void FUN_10c1b800(FArchive& Ar);

    char Unknown04[0x44];
    UObject* Unknown48;
    bool Unknown4C;
};

// FUNCTION: 0x10C1B800 ?FUN_10c1b800@Class_10E98D50@@UAEXAAVFArchive@@@Z
void Class_10E98D50::FUN_10c1b800(FArchive& Ar)
{
    FUN_10c1b1a0(Ar);
    Ar.Virtual6(&Unknown48);
    if (Ar.Unknown0C >= 0x40)
        Ar.Serialize(&Unknown4C, 1);
}

// FUNCTION: 0x10C1B930 ?FUN_10c1b930@Class_10C1B930@@QAEXXZ
void Class_10C1B930::FUN_10c1b930()
{
    Unknown2C = 0;
    Unknown3C = 0;
    Unknown34 = 0;
    Unknown47 = 1;
}
