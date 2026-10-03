// Game/Unsorted_10A2F460.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10A905A0
{
public:
    Class_10A905A0() {}
    virtual ~Class_10A905A0();
};

class Class_10E66320 : public Class_10A905A0
{
public:
    Class_10E66320();
    virtual ~Class_10E66320();
    virtual Class_10E66320* Virtual1();
    virtual int FUN_10a2f0c0(Class_10E66320* Other);
    virtual bool FUN_10a2f0f0(int p1);
    virtual void FUN_109b1f50(FString* p1);
    virtual FString* FUN_10a2f510();

    FString Unknown04;
    int Unknown10;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// Slot 0 of this vtable is a scalar deleting destructor, like the other classes
// cloned in this range (0x10A2F1D0, 0x10A2F300).
class Class_10E5D5E0
{
public:
    Class_10E5D5E0() : Unknown04(0) {}

    virtual void Virtual0();

    int Unknown04;
};

class Class_10E66310 : public Class_10E5D5E0
{
public:
    Class_10E66310() : Unknown08(1) {}

    virtual Class_10E66310* FUN_10a2f460();

    int Unknown08;
};

// FUNCTION: 0x10A2F460 ?FUN_10a2f460@Class_10E66310@@UAEPAV1@XZ
Class_10E66310* Class_10E66310::FUN_10a2f460()
{
    Class_10E66310* Copy = new(0, 0, 0, 0, 0) Class_10E66310();
    Copy->Unknown08 = Unknown08;
    Copy->Unknown04 = Unknown04;
    return Copy;
}

// FUNCTION: 0x10A2F4C0 ??0Class_10E66320@@QAE@XZ
Class_10E66320::Class_10E66320()
{
    Unknown10 = 0;
}

// FUNCTION: 0x10A2FB80 ??_GClass_10E66320@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10A2F4C0's definition in this unit.
