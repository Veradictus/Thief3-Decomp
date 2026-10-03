// Game/Unsorted_10B49250_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AGarrett
{
public:
    void FUN_10b21b90(int A);

    char Unknown00[0x450];
    unsigned bInBowDraw : 1;
    unsigned isCrouching : 1;
    unsigned CanDoItemSearch : 1;
    unsigned CanUseItems : 1;
    unsigned bUpdatePhysHeight : 1;
};

class Class_10B39530
{
public:
    void FUN_10b39530(int A, float B, float C, int D, int E, int F, float G);
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10B3AE70 : public Class_10AA82D0
{
public:
    virtual void Virtual1();

    void FUN_10b3ae70(AGarrett* Garrett);

    char Unknown04[0xC];
};

class Class_10E7E658 : public Class_10B3AE70
{
public:
    void FUN_10b3b030(AGarrett* Garrett);
};

class Class_10E7E610 : public Class_10E7E658
{
public:
    virtual void FUN_10b492f0(AGarrett* Garrett);

    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

// FUNCTION: 0x10B492F0 ?FUN_10b492f0@Class_10E7E610@@UAEXPAVAGarrett@@@Z
void Class_10E7E610::FUN_10b492f0(AGarrett* Garrett)
{
    Unknown10 = 1;
    FUN_10b3ae70(Garrett);
    ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(0x48, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    FUN_10b3b030(Garrett);
    Unknown18 = 0;
    Unknown20 = 1;
    Unknown1C = 1;
    Garrett->bUpdatePhysHeight = 0;
    Garrett->FUN_10b21b90(1);
}
