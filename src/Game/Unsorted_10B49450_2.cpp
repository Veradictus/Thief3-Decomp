// Game/Unsorted_10B49450_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10B3AE70
{
public:
    virtual void Virtual0();
    virtual void Virtual1();

    void FUN_10b3ae70(AGarrett* Garrett);

    char Unknown04[0xC];
};

class Class_10E7E658 : public Class_10B3AE70
{
public:
    virtual void FUN_10b49450(AGarrett* Garrett);

    void FUN_10b3b030(AGarrett* Garrett);

    bool Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

// FUNCTION: 0x10B49450 ?FUN_10b49450@Class_10E7E658@@UAEXPAVAGarrett@@@Z
void Class_10E7E658::FUN_10b49450(AGarrett* Garrett)
{
    Unknown10 = true;
    FUN_10b3ae70(Garrett);
    Unknown18 = 0;
    Unknown20 = 1;
    Unknown1C = 1;
    FUN_10b3b030(Garrett);
    Unknown14 = 0;
    DAT_10f3a3d8->Unknown108->FUN_109e38b0((int)Garrett->ropeToMount, (int)&Garrett->Location);
    Garrett->bUpdatePhysHeight = 0;
    Garrett->FUN_10b21b90(1);
}
