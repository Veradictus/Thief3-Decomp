// Game/Unsorted_10B461D0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10AF7F80;

void FUN_10a51fc0(FVector& Out, const FString& Prefix, Class_10AF7F80* File, Class_10AF7F80* Section);

class Window
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void LoadConfig(Class_10AF7F80* File, Class_10AF7F80* Section);
};

class Class_10E67BD8 : public Window
{
public:
    virtual void LoadConfig(Class_10AF7F80* File, Class_10AF7F80* Section);
};

class Class_10E7F770 : public Class_10E67BD8
{
public:
    virtual void LoadConfig(Class_10AF7F80* File, Class_10AF7F80* Section);

    char Unknown04[0x150];
    FVector Unknown154;
};

// FUNCTION: 0x10B46C90 ?LoadConfig@Class_10E7F770@@UAEXPAVClass_10AF7F80@@0@Z
void Class_10E7F770::LoadConfig(Class_10AF7F80* File, Class_10AF7F80* Section)
{
    Class_10E67BD8::LoadConfig(File, Section);
    Unknown154 = FVector(0.0f, 0.0f, 0.0f);
    FUN_10a51fc0(Unknown154, "ClearPos_", File, Section);
}
