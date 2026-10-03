// Game/Unsorted_10B4BD80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class AGarrett
{
public:
    char Unknown00[0x38];
    FRotator Rotation;
    char Unknown44[0x3BC];
    FRotator HeadRot;
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

    char Unknown04[4];
    int Unknown08;
    int Unknown0C;
};

class Class_10E7E730 : public Class_10B3AE70
{
public:
    void FUN_10b3b0b0(AGarrett* Garrett);
};

class Class_10E7E898 : public Class_10E7E730
{
public:
    virtual void FUN_10b4bd80(AGarrett* Garrett);

    float Unknown10;
};

// FUNCTION: 0x10B4BD80 ?FUN_10b4bd80@Class_10E7E898@@UAEXPAVAGarrett@@@Z
void Class_10E7E898::FUN_10b4bd80(AGarrett* Garrett)
{
    FUN_10b3b0b0(Garrett);
    Garrett->HeadRot = Garrett->Rotation;
    Unknown10 = 2.0f;
    Unknown08 = 0x100;
    ((Class_10B39530*)FUN_10aa82d0())->FUN_10b39530(0x100, -1.0f, 1.0f, 0x101, 0, 0, -1.0f);
}
