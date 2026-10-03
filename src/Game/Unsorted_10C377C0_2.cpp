// Game/Unsorted_10C377C0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Object_10BCE8D0;

class Class_10C08940
{
public:
    char Unknown00[0x2C];
    FVector Unknown2C;
};

class Class_10978090
{
public:
    Class_10C08940* FUN_10978090();

    void* Unknown00;
    Class_10C08940* Unknown04;
};

class Class_10E9AF04
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
};

class Class_10E9AE24 : public Class_10E9AF04
{
public:
    virtual void FUN_10c37860(Object_10BCE8D0* A);
    virtual FVector FUN_10c377c0();

    char Unknown04[0x48];
    Class_10978090 Unknown4C;
    char Unknown54[0x28];
    FVector Unknown7C;
    char Unknown88[0xC];
    float Unknown94;
    float Unknown98;
};

// FUNCTION: 0x10C377C0 ?FUN_10c377c0@Class_10E9AE24@@UAE?AVFVector@@XZ
FVector Class_10E9AE24::FUN_10c377c0()
{
    if (!Unknown4C.FUN_10978090())
        return FVector(0.0f, 0.0f, 0.0f);
    FVector Location = Unknown4C.FUN_10978090()->Unknown2C;
    Location.X += Unknown94;
    Location.Y += Unknown98;
    Location += Unknown7C;
    return Location;
}
