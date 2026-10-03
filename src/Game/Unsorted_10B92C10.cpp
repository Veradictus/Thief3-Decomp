// Game/Unsorted_10B92C10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10990D10
{
public:
    void FUN_10990d10();
};

class Class_10E894C8
{
public:
    virtual void FUN_10b92cb0(int p1);

    Class_10990D10* Unknown04;
};

class FCoords
{
public:
    FCoords(const FVector& InOrigin) : Origin(InOrigin), XAxis(1, 0, 0), YAxis(0, 1, 0), ZAxis(0, 0, 1) {}

    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
};

class Class_10B92DB0
{
public:
    Class_10B92DB0* FUN_10b92db0();

    FCoords Unknown00;
    FVector Unknown30;
    FLOAT Unknown3C;
    FLOAT Unknown40;
    FLOAT Unknown44;
    INT Unknown48;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E89A8C
{
public:
    Class_10E89A8C(int Value) : Unknown04(Value) {}

    virtual ~Class_10E89A8C();
    virtual Class_10E89A8C* FUN_10b92c10();

    int Unknown04;
};

// FUNCTION: 0x10B92C10 ?FUN_10b92c10@Class_10E89A8C@@UAEPAV1@XZ
Class_10E89A8C* Class_10E89A8C::FUN_10b92c10()
{
    return new(0, 0, 0, 0, 0) Class_10E89A8C(Unknown04);
}

// FUNCTION: 0x10B92CB0 ?FUN_10b92cb0@Class_10E894C8@@UAEXH@Z
void Class_10E894C8::FUN_10b92cb0(int p1)
{
    if (Unknown04)
        Unknown04->FUN_10990d10();
}

// FUNCTION: 0x10B92DB0 ?FUN_10b92db0@Class_10B92DB0@@QAEPAV1@XZ
Class_10B92DB0* Class_10B92DB0::FUN_10b92db0()
{
    Unknown00.FCoords::FCoords(FVector(0, 0, 0));
    Unknown30.X = 0.0f;
    Unknown30.Y = 1.0f;
    Unknown30.Z = 0.0f;
    Unknown3C = 0.05f;
    Unknown40 = 0.5f;
    Unknown44 = 0.4f;
    Unknown48 = 0;
    return this;
}
