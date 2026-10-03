// Game/Unsorted_10A2EFA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10E66320
{
public:
    virtual ~Class_10E66320();
    virtual Class_10E66320* Virtual1();
    virtual int FUN_10a2f0c0(Class_10E66320* Other);
    virtual bool FUN_10a2f0f0(int p1);
    virtual void FUN_109b1f50(FString* p1);
    virtual FString* FUN_10a2f510();

    FString Unknown04;
    int Unknown10;
};

class Class_10E66350 : public Class_10E66320
{
public:
    Class_10E66350();
    virtual ~Class_10E66350();
    virtual int FUN_10a2f0c0(Class_10E66320* Other);

    int Unknown14;
    FString Unknown18;
    FString Unknown24;
    int Unknown30;
    int Unknown34;
};

class Class_10E66368 : public Class_10E66350
{
public:
    Class_10E66368();
    virtual ~Class_10E66368();
    virtual Class_10E66320* Virtual1();
    virtual int FUN_10a2f0c0(Class_10E66320* Other);
    virtual bool FUN_10a2f0f0(int p1);

    int Unknown38;
};

// FUNCTION: 0x10A2F0C0 ?FUN_10a2f0c0@Class_10E66368@@UAEHPAVClass_10E66320@@@Z
int Class_10E66368::FUN_10a2f0c0(Class_10E66320* Other)
{
    int Mine = Unknown38;
    int Theirs = static_cast<Class_10E66368*>(Other)->Unknown38;
    if ((Mine == 0 || Theirs == 0 || Mine == Theirs) && Class_10E66350::FUN_10a2f0c0(Other))
        return 1;
    return 0;
}
