// Game/AGarrett_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "T3Player/T3PlayerClasses.h"

class Class_10C56E40_Field00
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10C56E40
{
public:
    Class_10C56E40(Class_10C56E40_Field00* P)
    {
        Unknown00 = P;
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10C56E40();

    Class_10C56E40_Field00* Unknown00;
};

class Class_10E9C330
{
public:
    virtual void Virtual0(Class_10C56E40 A);
};

Class_10E9C330* FUN_10c56cf0();

// FUNCTION: 0x10B21630 ?Destroy@AGarrett@@UAEXXZ
void AGarrett::Destroy()
{
    Super::Destroy();
    FUN_10c56cf0()->Virtual0(0);
}
