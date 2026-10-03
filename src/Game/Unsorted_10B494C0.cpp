// Game/Unsorted_10B494C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AActor;

class FVector
{
public:
    float X;
    float Y;
    float Z;
};

class AGarrett
{
public:
    void FUN_10b21b90(int A);

    char Unknown00[0x2C];
    FVector Location;
    char Unknown38[0x2EC];
    AActor* ropeToMount;
    char Unknown328[0x128];
    unsigned bInBowDraw : 1;
    unsigned isCrouching : 1;
    unsigned CanDoItemSearch : 1;
    unsigned CanUseItems : 1;
    unsigned bUpdatePhysHeight : 1;
};

class Class_10B396A0
{
public:
    void FUN_10b396a0();
};

class Class_10E7ED00
{
public:
    void FUN_109e38b0(int A, int B);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x108];
    Class_10E7ED00* Unknown108;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10B3ADC0 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();

    void FUN_10b3ae90(AGarrett* Garrett);
    void FUN_10b3b130(AGarrett* Garrett);
};

class Class_10E7E658 : public Class_10B3ADC0
{
public:
    virtual void FUN_10b494c0(AGarrett* Garrett);
};

// FUNCTION: 0x10B494C0 ?FUN_10b494c0@Class_10E7E658@@UAEXPAVAGarrett@@@Z
void Class_10E7E658::FUN_10b494c0(AGarrett* Garrett)
{
    FUN_10b3ae90(Garrett);
    FUN_10b3b130(Garrett);
    ((Class_10B396A0*)FUN_10aa82d0())->FUN_10b396a0();
    DAT_10f3a3d8->Unknown108->FUN_109e38b0((int)Garrett->ropeToMount, (int)&Garrett->Location);
    Garrett->bUpdatePhysHeight = 1;
    Garrett->FUN_10b21b90(0);
}
