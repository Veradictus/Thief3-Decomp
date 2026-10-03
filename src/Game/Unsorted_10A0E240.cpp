// Game/Unsorted_10A0E240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_109709F0
{
public:
    void FUN_109709f0();

    char Unknown00[0x18];
};

class Class_10AF4BB0
{
public:
    void FUN_10af3bd0(int A, int B, int C);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A0E240 : public Class_10AF4BB0
{
public:
    void FUN_10a0e240(int Index, int Count);
};

class Class_10905530
{
public:
    ~Class_10905530();

    char Unknown00[0xC];
};

class Class_10A0E3E0
{
public:
    ~Class_10A0E3E0();

    int Unknown00;
    FString Unknown04;
    char Unknown10[8];
    Class_10905530 Unknown18;
};

// FUNCTION: 0x10A0E240 ?FUN_10a0e240@Class_10A0E240@@QAEXHH@Z
void Class_10A0E240::FUN_10a0e240(int Index, int Count)
{
    for (int i = Index; i < Index + Count; i++)
        ((Class_109709F0*)Unknown00)[i].FUN_109709f0();
    FUN_10af3bd0(Index, Count, 0x18);
}

// FUNCTION: 0x10A0E3E0 ??1Class_10A0E3E0@@QAE@XZ
Class_10A0E3E0::~Class_10A0E3E0()
{
}
