// Game/Unsorted_10B12D80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10B12120
{
public:
    ~Class_10B12120();

    FString Unknown00;
    FString Unknown0C;
    int Unknown18;
};

class Class_10AF4BB0
{
public:
    void FUN_10af3bd0(int A, int B, int C);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B12D80 : public Class_10AF4BB0
{
public:
    void FUN_10b12d80(int Index, int Count);
};

// FUNCTION: 0x10B12D80 ?FUN_10b12d80@Class_10B12D80@@QAEXHH@Z
void Class_10B12D80::FUN_10b12d80(int Index, int Count)
{
    for (int i = Index; i < Index + Count; i++)
        ((Class_10B12120*)Unknown00)[i].~Class_10B12120();
    FUN_10af3bd0(Index, Count, 0x1C);
}
