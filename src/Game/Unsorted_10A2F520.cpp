// Game/Unsorted_10A2F520.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUNCTION: 0x10A2F8C0 ??0Class_10E66368@@QAE@XZ
Class_10E66368::Class_10E66368()
{
    Unknown38 = 0;
}

// FUNCTION: 0x10A2FBE0 ??_GClass_10E66368@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10A2F8C0's definition in this unit.
