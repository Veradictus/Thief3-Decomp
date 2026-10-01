// Game/Unsorted_10C1ADC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10C1ADE0
{
public:
    char Unknown00[0x2C];
    FVector Unknown2C;
};

class Class_10E98FD8
{
public:
    virtual void Virtual0();
    virtual bool FUN_10c1ade0(FVector* Out, int Unused);

    Class_10C1ADE0* Unknown04;
};

struct Data_10C1AED0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Info_10C1AED0
{
    char Unknown00[0x38];
    Data_10C1AED0 Unknown38;
};

class Class_10E98D50
{
public:
    virtual void Virtual0();
    virtual bool FUN_10c1aed0(Data_10C1AED0* Out, int B);

    char Unknown04[0x44];
    Info_10C1AED0* Unknown48;
};

class Class_10E98F90
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10c1af40(Class_10E98F90* Other);

    char Unknown04[0x20];
    float Unknown24;
};

// FUNCTION: 0x10C1ADE0 ?FUN_10c1ade0@Class_10E98FD8@@UAE_NPAVFVector@@H@Z
bool Class_10E98FD8::FUN_10c1ade0(FVector* Out, int Unused)
{
    if (Unknown04) {
        *Out = Unknown04->Unknown2C;
        return true;
    }
    return false;
}

// FUNCTION: 0x10C1AED0 ?FUN_10c1aed0@Class_10E98D50@@UAE_NPAUData_10C1AED0@@H@Z
bool Class_10E98D50::FUN_10c1aed0(Data_10C1AED0* Out, int B)
{
    if (Unknown48 != 0)
    {
        *Out = Unknown48->Unknown38;
        return true;
    }
    return false;
}

// FUNCTION: 0x10C1AF40 ?FUN_10c1af40@Class_10E98F90@@UAEHPAV1@@Z
int Class_10E98F90::FUN_10c1af40(Class_10E98F90* Other)
{
    if (Other->Unknown24 == Unknown24)
        return 1;
    return 0;
}
