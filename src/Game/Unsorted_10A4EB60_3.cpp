// Game/Unsorted_10A4EB60_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10BB7C00
{
public:
    void FUN_10bb7c00();

    FString Unknown00;
    char Unknown0C[0x10];
};

class Class_10AF4BB0
{
public:
    void FUN_10af3bd0(int A, int B, int C);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A4FC00 : public Class_10AF4BB0
{
public:
    void FUN_10a4fc00(int Slack);
    void FUN_10a4fc50(int Index, int Count);
};

// FUNCTION: 0x10A4FC50 ?FUN_10a4fc50@Class_10A4FC00@@QAEXHH@Z
void Class_10A4FC00::FUN_10a4fc50(int Index, int Count)
{
    for (int i = Index; i < Index + Count; i++)
        ((Class_10BB7C00*)Unknown00)[i].FUN_10bb7c00();
    FUN_10af3bd0(Index, Count, 0x1c);
}
