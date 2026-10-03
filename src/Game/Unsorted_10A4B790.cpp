// Game/Unsorted_10A4B790.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class ULinkDataObject;

class UUserLinkDataObject
{
    DECLARE_CLASS(UUserLinkDataObject, ULinkDataObject, 0x0, Engine)
};

class Class_10E77578
{
public:
    virtual void Virtual0();
    virtual void Virtual1(int A, int B, UClass* C, int D);
};

Class_10E77578* FUN_10b0b2b0();

class Class_10E67938
{
public:
    virtual void Virtual0(int Code, int A, int B, int C);
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(int A, int B);
    virtual void Virtual4(int A, int B);
};

// FUNCTION: 0x10A4C050 ?Virtual3@Class_10E67938@@UAEXHH@Z
void Class_10E67938::Virtual3(int A, int B)
{
    Virtual4(0x2f186b8, A);
    FUN_10b0b2b0()->Virtual1(A, B, UUserLinkDataObject::StaticClass(), 0x2f186b8);
}
