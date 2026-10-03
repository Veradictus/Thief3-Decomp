// Game/Unsorted_10BB8430.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10c00480();

class Class_10BB8480
{
public:
    bool FUN_10bb8480();

    char Unknown00[0x2C4];
    float Unknown2C4;
};

class Class_10BA9F90
{
public:
    void FUN_10ba9f90(int A);
};

class Class_10C28BD0
{
public:
    void FUN_10c28bd0();
};

int FUN_10c28bc0();

class Class_10BBDB40
{
public:
    float FUN_10bbdb40();
};

class Class_10DBD510 : public Class_10BA9F90
{
public:
    Class_10BBDB40* FUN_10dbd510(int A);
};

class Class_10BB8430
{
public:
    void FUN_10bb7f90();
    void FUN_10bb8430();

    char Unknown00[8];
    Class_10DBD510* Unknown08;
    char Unknown0C[0x2B8];
    float Unknown2C4;
};

// FUNCTION: 0x10BB8430 ?FUN_10bb8430@Class_10BB8430@@QAEXXZ
void Class_10BB8430::FUN_10bb8430()
{
    Unknown08->FUN_10ba9f90(0);
    ((Class_10C28BD0*)FUN_10c28bc0())->FUN_10c28bd0();
    FUN_10bb7f90();
    float Value = Unknown08->FUN_10dbd510(0x10070a)->FUN_10bbdb40();
    Unknown2C4 = FUN_10c00480() + Value;
}

// FUNCTION: 0x10BB8480 ?FUN_10bb8480@Class_10BB8480@@QAE_NXZ
bool Class_10BB8480::FUN_10bb8480()
{
    if (FUN_10c00480() > Unknown2C4)
        return true;
    return false;
}
