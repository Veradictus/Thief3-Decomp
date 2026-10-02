// Game/Unsorted_10B488E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AGarrett
{
public:
    char Unknown00[0x450];
    unsigned bInBowDraw : 1;
    unsigned isCrouching : 1;
};

class Class_10B39530
{
public:
    void FUN_10b39530(int A, float B, float C, int D, int E, int F, float G);
};

class Class_10AC92E0
{
public:
    void FUN_10ac92e0();
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x13C];
    Class_10AC92E0* Unknown13C;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10E7E580 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void FUN_10b49120(AGarrett* Garrett);
};

// FUNCTION: 0x10B49120 ?FUN_10b49120@Class_10E7E580@@UAEXPAVAGarrett@@@Z
void Class_10E7E580::FUN_10b49120(AGarrett* Garrett)
{
    if (Garrett->isCrouching)
        ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(1, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    else
        ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(0, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
    DAT_10f3a3d8->Unknown13C->FUN_10ac92e0();
}
